#include "library.h"

#include <iostream>
#include <iomanip>
/// \param val the value of this node.
AvlTree::Node::Node(int const val) : key(val) {

}

/// \param val the value of the node.
/// \param left the left child node.
/// \param right the right child node.
AvlTree::Node::Node(int const val, Node *left, Node *right) : key(val), left(left), right(right) {

}

AvlTree::Node::~Node() {
    if (left != nullptr) {
        delete (left);
    }
    if (right != nullptr) {
        delete (right);
    }
}

int AvlTree::Node::childs() const {
    if (left == nullptr && right == nullptr)
        return 0;
    if (left == nullptr || right == nullptr)
        return 1;
    return 2;
}

/// \param child the type of child should be fetched.
AvlTree::Node *AvlTree::Node::getChild(Child child) const {
    if (child == Child::left)
        return this->left;
    return this->right;
}

AvlTree::~AvlTree() {
    if (root != nullptr) {
        delete root;
    }
}

/// \param key the key of the node to find.
bool AvlTree::search(int const key) const {
    Node *element = root;

    while (element != nullptr) {
        if (element->key == key)
            return true;
        if (key > element->key)
            element = element->right;
        else
            element = element->left;
    }
    return false;

}

/// \param key the node to remove.
bool AvlTree::remove(int const key) {

    if (root == nullptr)
        return false;
    Node *element = root;
    while (true) {
        if (element->key == key) {
            break;
        }
        if (key > element->key && element->right) {
            element = element->right;
        } else if (key < element->key && element->left) {
            element = element->left;
        } else {
            return false;
        }
    }
    //Maybe the rool shall be deleted.
    switch (element->childs()) {
        case 0:
            deleteWithoutChild(element);
            break;
        case 1: {
            deleteWithOneChild(element);
            break;
        }
        case 2: {
            //go once left and then go right until end to get element fitting in spot of deleting element
            Node *tmp = element->left;
            while (tmp->right != nullptr) {
                tmp = tmp->right;
            }
            int elemKey = element->key;
            element->key = tmp->key;
            tmp->key = elemKey;
            //Achtung hier kein AVL-Baum! Erst nach remove
            if (tmp->childs() == 0) {
                deleteWithoutChild(tmp);
            } else {
                deleteWithOneChild(tmp);
            }
            break;
        }
    }

}

/// \param element the element to delete.
void AvlTree::deleteWithoutChild(AvlTree::Node *element) {
    if (element->previous) {
        bool isLeft = element->previous->left == element;
        if (isLeft) {
            element->previous->left = nullptr;
            if (element->previous->right == nullptr) {
                //height of q 0
                element->previous->balance = 0;
                upout(element->previous);
            } else {
                if (element->previous->right->childs() == 0) {
                    //height of q 1
                    element->previous->balance = 1;
                } else {
                    //height of q 2
                    Node *rotatedRoot = nullptr;
                    if (element->previous->right->balance == 1) {
                        rotatedRoot = rotateLeft(element->previous);
                    } else {
                        rotatedRoot = rotateRightLeft(element->previous);
                    }
                    fixBalancesDelete(rotatedRoot);
                }
            }

        } else {
            element->previous->right = nullptr;
            if (element->previous->left == nullptr) {
                //height of q 0
                element->previous->balance = 0;
                upout(element->previous);
            } else {
                if (element->previous->left->childs() == 0) {
                    //height of q 1
                    element->previous->balance = -1;
                } else {
                    //height of q 2
                    Node *rotatedRoot = nullptr;
                    if (element->previous->left->balance == -1) {
                        rotatedRoot = rotateRight(element->previous);
                    } else {
                        rotatedRoot = rotateLeftRight(element->previous);
                    }
                    fixBalancesDelete(rotatedRoot);
                }
            }

        }

    } else {
        root = nullptr;
    }
    delete element;
}

/// \param rotatedRoot the new root of the "subtree"
void AvlTree::fixBalancesDelete(AvlTree::Node *rotatedRoot) {//calc balance of right
    //calc balance of left child
    fixBalancesChild(rotatedRoot, Child::left);
    //Fix balances of the right child
    fixBalancesChild(rotatedRoot, Child::right);
    //calc balance of root
    if (rotatedRoot->left->childs() > 0 && rotatedRoot->right->childs() == 0) {
        rotatedRoot->balance = -1;
    } else if (rotatedRoot->left->childs() == 0 && rotatedRoot->right->childs() > 0) {
        rotatedRoot->balance = 1;
    } else {
        upout(rotatedRoot);
    }
}

/// \param rotatedRoot the root to fetch the child.
/// \param child the child to fix (left or right)
void AvlTree::fixBalancesChild(const AvlTree::Node *rotatedRoot, Child child) const {
    if (rotatedRoot->getChild(child)->childs() == 2) {
        rotatedRoot->getChild(child)->balance = 0;
    } else if (rotatedRoot->getChild(child)->right) {
        rotatedRoot->getChild(child)->balance = 1;
    } else if (rotatedRoot->getChild(child)->left) {
        rotatedRoot->getChild(child)->balance = -1;
    } else {
        rotatedRoot->getChild(child)->balance = 0;
    }
}

/// \param element the node to delete.
void AvlTree::deleteWithOneChild(AvlTree::Node *element) {
    Node *child = element->left ? element->left : element->right;
    element->key = child->key;
    element->right = nullptr;
    element->left = nullptr;
    element->balance = 0;
    if (element->previous) {
        upout(element);
    }
    delete child;
}

/// \param input the parent node of the removed node.
void AvlTree::upout(AvlTree::Node *input) {
    if (input->previous) {
        if (input == input->previous->left) {
            if (input->previous->balance == -1) {
                input->previous->balance = 0;
                upout(input->previous);
                return;
            } else if (input->previous->balance == 0) {
                input->previous->balance = 1;
                return;
            } else {
                if (input->previous->right->balance == 0) {
                    Node *root = rotateLeft(input->previous);
                    root->balance = -1;
                    root->left->balance = 1;
                    root->left->left->balance = 0;
                } else if (input->previous->right->balance == 1) {
                    Node *root = rotateLeft(input->previous);
                    root->balance = 0;
                    root->left->balance = 0;
                    root->left->left->balance = 0;
                    upout(root);
                } else {
                    int balanceRightLeft = input->previous->right->left->balance;
                    Node *root = rotateRightLeft(input->previous);
                    root->balance = 0;
                    root->left->left->balance = 0;
                    root->left->balance = 0;
                    root->right->balance = 0;
                    if (balanceRightLeft == 1) {
                        root->left->balance = -1;
                    } else if (balanceRightLeft == -1) {
                        root->right->balance = 1;
                    }
                    upout(root);
                }
            }
        } else {
            if (input->previous->balance == 1) {
                input->previous->balance = 0;
                upout(input->previous);
                return;
            } else if (input->previous->balance == 0) {
                input->previous->balance = -1;
                return;
            } else {
                if (input->previous->left->balance == 0) {
                    Node *root = rotateRight(input->previous);
                    root->balance = 1;
                    root->right->balance = -1;
                    root->right->right->balance = 0;
                } else if (input->previous->left->balance == -1) {
                    Node *root = rotateRight(input->previous);
                    root->balance = 0;
                    root->right->balance = 0;
                    root->right->right->balance = 0;
                    upout(root);
                } else {

                    int balanceLeftRight = input->previous->left->right->balance;
                    Node *root = rotateLeftRight(input->previous);
                    root->balance = 0;
                    root->right->right->balance = 0;
                    root->left->balance = 0;
                    root->right->balance = 0;
                    if (balanceLeftRight == 1) {
                        root->left->balance = -1;
                    } else if (balanceLeftRight == -1) {
                        root->right->balance = 1;
                    }
                    upout(root);
                }
            }

        }

    }


}

/// \param key the key to insert.
bool AvlTree::insert(int const key) {

    Node *toInsert = new Node(key);

    if (root == nullptr) {
        root = toInsert;
        return true;
    }

    Node *element = root;

    while (true) {
        if (element->key == key) {
            //New node is not needed anymore!
            delete toInsert;

            return false;
        }
        if (key > element->key && element->right) {
            element = element->right;
        } else if (key < element->key && element->left) {
            element = element->left;
        } else {
            break;
        }
    }
    toInsert->previous = element;
    if (key > element->key) {
        element->right = toInsert;
        element->balance += 1;
    } else {
        element->left = toInsert;
        element->balance -= 1;
    }
    if (element->balance != 0) {
        upin(element);
    }

    return true;
}

/// \param input the root which was modified by adding and rotating a node..
void AvlTree::upin(AvlTree::Node *input) {
    if (input != nullptr && input->previous != nullptr) {
        Node *previous = input->previous;
        if (input == previous->left) {
            if (previous->balance == -1 && input->balance == -1) {
                rotateRight(previous);
            } else if (previous->balance == -1 && input->balance == 1) {
                rotateLeftRight(previous);
            } else if (previous->balance == 1) {
                previous->balance = 0;
            } else if (previous->balance == 0) {
                previous->balance = -1;
                upin(previous);
            }
            return;
        } else if (input == previous->right) {
            if (previous->balance == 1 && input->balance == 1) {
                rotateLeft(previous);
            } else if (previous->balance == 1 && input->balance == -1) {
                rotateRightLeft(previous);
            } else if (previous->balance == -1) {
                previous->balance = 0;
            } else if (previous->balance == 0) {
                previous->balance = 1;
                upin(previous);
            }
            return;
        }
    }
}

/// \param input the old root of the (sub)tree which shal be used for rotating.
AvlTree::Node *AvlTree::rotateLeft(AvlTree::Node *input) {
    Node *inputRightLeft = input->right->left;
    Node *inputPrevious = input->previous;
    Node *inputRight = input->right;

    if (inputPrevious != nullptr) {
        if (inputPrevious->left == input) {
            inputPrevious->left = inputRight;
        } else {
            inputPrevious->right = inputRight;
        }
        inputRight->previous = inputPrevious;
    } else {
        root = inputRight;
        inputRight->previous = nullptr;
    }
    inputRight->left = input;
    input->previous = inputRight;
    input->right = inputRightLeft;
    if (inputRightLeft) {
        inputRightLeft->previous = input;
    }
    input->balance = 0;
    inputRight->balance = 0;
    return inputRight;
};

/// \param input the old root of the (sub)tree which shal be used for rotating.
AvlTree::Node *AvlTree::rotateRight(AvlTree::Node *input) {
    Node *inputLeftRight = input->left->right;
    Node *inputPrevious = input->previous;
    Node *inputLeft = input->left;

    if (inputPrevious != nullptr) {

        if (inputPrevious->left == input) {
            inputPrevious->left = inputLeft;
        } else {
            inputPrevious->right = inputLeft;
        }
        inputLeft->previous = inputPrevious;
    } else {
        root = inputLeft;
        inputLeft->previous = nullptr;
    }
    inputLeft->right = input;
    input->previous = inputLeft;
    input->left = inputLeftRight;
    if (inputLeftRight) {
        inputLeftRight->previous = input;
    }
    input->balance = 0;
    inputLeft->balance = 0;
    return inputLeft;
};

/// \param input the old root of the (sub)tree which shal be used for rotating.
AvlTree::Node *AvlTree::rotateLeftRight(AvlTree::Node *input) {
    Node *tmp = input->left->right;
    bool leftSmaller = true;
    if (tmp->balance == -1) {
        leftSmaller = false;
    }
    rotateLeft(input->left);
    Node *toReturn = rotateRight(input);
    if (leftSmaller && toReturn->left->childs() != 0) {
        toReturn->left->balance = -1;
    } else if ( !leftSmaller && toReturn->right->childs() != 0){
        toReturn->right->balance = 1;
    }
    return toReturn;
};

/// \param input the old root of the (sub)tree which shal be used for rotating.
AvlTree::Node *AvlTree::rotateRightLeft(AvlTree::Node *input) {
    Node *tmp = input->right->left;
    bool leftSmaller = true;
    if (tmp->balance == -1) {
        leftSmaller = false;
    }
    rotateRight(input->right);
    Node *toReturn = rotateLeft(input);
    if (leftSmaller && toReturn->left->childs() != 0) {
        toReturn->left->balance = -1;
    } else if ( !leftSmaller && toReturn->right->childs() != 0){
        toReturn->right->balance = 1;
    }
    return toReturn;
};

ostream &operator<<(ostream &stream, AvlTree &tree) {
    tree.display();
    return cout;
};

void AvlTree::display() {
    cout << "Tree" << endl;
    display(root, 0);
}

void AvlTree::display(AvlTree::Node *current, int indent) {
    if (current != nullptr) {
        display(current->right, indent + 10);
        if (indent > 0)
            cout << setw(indent) << " ";
        cout << current->key << endl;
        display(current->left, indent + 10);
    }
}

AvlTree &operator+=(AvlTree &tree, int const param) {
    tree.insert(param);
    return tree;
};

AvlTree &operator-=(AvlTree &tree, int const param) {
    tree.remove(param);
    return tree;
};

bool AvlTree::isBalanced() {
    isBalanced(root);
}

/* Returns true if binary tree with root as root is height-balanced */
bool AvlTree::isBalanced(AvlTree::Node *root) {

    if (root == nullptr)
        return true;

    int lh = height(root->left);
    int rh = height(root->right);
    return abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

int AvlTree::height(AvlTree::Node *node) {
    if (node == nullptr)
        return 0;

    return 1 + max(height(node->left), height(node->right));
}