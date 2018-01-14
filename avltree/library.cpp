#include "library.h"

/*
 * Constructor
 */
AvlTree::Node::Node(int const val) :
    key(val) {
}

/*
 * Constructor
 */
AvlTree::Node::Node(int const val, Node *left, Node *right) :
    key(val), left(left), right(right) {
}

/*
 * Destructor
 */
AvlTree::Node::~Node() {
    if (left != nullptr) delete (left);
    if (right != nullptr) delete (right);
}

/*
 * Destructor
 */
AvlTree::~AvlTree() {
    if (head != nullptr) delete head;
}

/*
 * Number of Childs of the Node.
 */
int AvlTree::Node::childs() const {
    int counter = 0;
    if (left != nullptr) counter++;
    if (right != nullptr) counter++;
    return counter;
}

AvlTree::Node *AvlTree::Node::getChild(Child c) const {
    if (c == Child::left) return left;
    return right;
}

bool AvlTree::search(int const key) const {
    auto tmp = head;
    while (tmp != nullptr) {
        if (key == tmp->key) return true;
        if (key < tmp->key) tmp = tmp->left;
        else tmp = tmp->right;
    }
    /*
     * If there is no "key" in the tree
     */
    return false;
}

/*
 * Case: Rotate Left
 */
AvlTree::Node *AvlTree::rotL(AvlTree::Node *node) {
    auto rl = node->right->left, p = node->previous, r = node->right;
    if (p != nullptr) {
        if (p->left != node) p->right = r;
        else p->left = r;
        r->previous = p;
    } else {
        head = r;
        r->previous = nullptr;
    }
    r->left = node;
    node->previous = r;
    node->right = rl;
    if (rl) rl->previous = node;
    node->balance = 0;
    r->balance = 0;
    return r;
};

/*
 * Case: Rotate Right
 */
AvlTree::Node *AvlTree::rotR(AvlTree::Node *node) {
    auto lr = node->left->right, p = node->previous, l = node->left;
    if (p == nullptr) {
        head = l;
        l->previous = nullptr;
    } else {
        if (p->left != node) p->right = l;
        else p->left = l;
        l->previous = p;
    }
    l->right = node;
    node->previous = l;
    node->left = lr;
    if (lr) lr->previous = node;
    l->balance = 0;
    node->balance = 0;
    return l;
};


/*
 * Case: Rotate Right, Left
 */
AvlTree::Node *AvlTree::rotRL(AvlTree::Node *input) {
    auto tmp = input->right->left;
    bool lessThanLeft = true;
    if (tmp->balance == -1) lessThanLeft = false;
    rotR(input->right);
    auto reTurn = rotL(input);
    if (!lessThanLeft && reTurn->right->childs() != 0) reTurn->left->balance = -1;
    else if (lessThanLeft && reTurn->left->childs() != 0) reTurn->right->balance = 1;
    return reTurn;
};

/*
 * Case: Rotate Left, Right
 */
AvlTree::Node *AvlTree::rotLR(AvlTree::Node *node) {
    auto tmp = node->left->right;
    bool lessThanRight = true;
    if (tmp->balance == -1) lessThanRight = false;
    rotL(node->left);
    auto reTurn = rotR(node);
    if (lessThanRight && reTurn->left->childs() != 0) reTurn->left->balance = -1;
    else if ( !lessThanRight && reTurn->right->childs() != 0) reTurn->right->balance = 1;
    return reTurn;
};

int AvlTree::height(AvlTree::Node* node) {
    if (node == nullptr) return 0;
    return max(height(node->left), height(node->right)) + 1;
}

bool AvlTree::isBalanced() {
    isBalanced(head);
}

bool AvlTree::isBalanced(Node* node) {
    if (node == nullptr) return true;
    int heightLeft = height(node->left);
    int heightRight = height(node->right);
    return abs(heightLeft - heightRight) < 2 && (isBalanced(node->right) && isBalanced(node->left));
}

bool AvlTree::insert(int const newKey) {
    auto insert = new Node(newKey);
    if (head == nullptr) {
        head = insert;
        return true;
    }
    auto tmp = head;
    bool insertNow = true;
    while (insertNow) {
        if (newKey > tmp->key && tmp->right) tmp = tmp->right;
        else if (newKey < tmp->key && tmp->left) tmp = tmp->left;
        else insertNow = false;
    }
    /*
     * connect the new node to tmp.
     */
    insert->previous = tmp;
    if (newKey > tmp->key) {
        tmp->right = insert;
        tmp->balance += 1;
    } else if (newKey < tmp->key) {
        tmp->left = insert;
        tmp->balance -= 1;
    }
    /*
     * if the balance of tmp, that means the previous node, has
     * lost balance, that means, that the tree should be balanced again.
     */
    if (tmp->balance != 0) {
        upin(tmp);
    }
}


void AvlTree::upin(AvlTree::Node *input) {
    if (input != nullptr && input->previous != nullptr) {
        auto previous = input->previous;
        if (input == previous->left) {
            if (previous->balance == -1 && input->balance == -1) rotR(previous);
            else if (previous->balance == -1 && input->balance == 1) rotLR(previous);
            else if (previous->balance == 1) previous->balance = 0;
            else if (previous->balance == 0) {
                previous->balance = -1;
                upin(previous);
            }
            return;
        } else {
            if (previous->balance == 1 && input->balance == -1) rotRL(previous);
            else if (previous->balance == 1 && input->balance == 1) rotL(previous);
            else if (previous->balance == -1) previous->balance = 0;
            else if (previous->balance == 0) {
                previous->balance = 1;
                upin(previous);
            }
            return;
        }
    }
}

AvlTree &operator+=(AvlTree &avlTree, int const avl) {
    avlTree.insert(avl);
    return avlTree;
}

void AvlTree::upout(Node *node) {


    if (node->previous) {

        //left side
        if (node == node->previous->left) {
            if (node->previous->balance == -1) {
                node->previous->balance = 0;
                upout(node->previous);
            } else if (node->previous->balance == 0) {
                node->previous->balance = 1;
                return;
            } else {
                if (node->previous->right->balance == 0) {
                    Node *newRoot = rotL(node->previous);
                    newRoot->balance = -1;
                    newRoot->left->balance = 1;
                    newRoot->left->left->balance = 0;
                } else if (node->previous->right->balance == 1) {
                    Node *newRoot = rotL(node->previous);
                    newRoot->balance = 0;
                    newRoot->left->balance = 0;
                    newRoot->left->left->balance = 0;
                } else {
                    //Doppelrotation rechts-links
                    //fehlt noch newRoot->left / right -> balance;
                    int oldQbalance = node->previous->right->left->balance;
                    Node *newRoot = rotRL(node->previous);
                    newRoot->balance = 0;
                    newRoot->left->left->balance = 0;
                    newRoot->right->balance = 0;
                    newRoot->left->balance = 0;
                    if(oldQbalance == 1) {
                        newRoot->left->balance = -1;
                    } else if(oldQbalance == -1) {
                        newRoot->right->balance = 1;
                    }
                    upout(newRoot);
                }
            }

            //right side

        }else {
                if (node->previous->right == node) {
                    if (node->previous->balance == -1) {
                        node->previous->balance = 0;
                        upout(node->previous);
                    } else if (node->previous->balance == 0) {
                        node->previous->balance = 0;
                        return;
                    } else {
                        if (node->previous->left->balance == 0) {
                            Node *newRoot = rotR(node->previous);
                            newRoot->balance = -1;
                            newRoot->right->balance = 1;
                            newRoot->right->right->balance = 0;
                        } else if (node->previous->left->balance == 1) {
                            Node *newRoot = rotR(node->previous);
                            newRoot->balance = 0;
                            newRoot->right->balance = 0;
                            newRoot->right->right->balance = 0;
                        } else {
                            //Doppelrotation links-rechts
                            //fehlt noch newRoot->left / right -> balance;
                            int oldQbalance = node->previous->left->right->balance;
                            Node *newRoot = rotLR(node->previous);
                            newRoot->balance = 0;
                            newRoot->right->right->balance = 0;
                            newRoot->right->balance = 0;
                            newRoot->left->balance = 0;
                            if(oldQbalance == 1) {
                                newRoot->left->balance = -1;
                            } else if(oldQbalance == -1) {
                                newRoot->right->balance = 1;
                            }
                            upout(newRoot);
                    }
                }
            }
        }
    }
}

AvlTree& operator-=(AvlTree &tree, int const avl) {
    tree.remove(avl);
    return tree;
}

bool AvlTree::remove(int const removeKey) {
    if(head == nullptr) {
        return false;
    }
    Node *node = head;
    while(removeKey != node->key) {
        if(removeKey == node->key) {
            break;
        } else if(removeKey < node->key && node->left != nullptr) {
            node = node->left;
        } else if(removeKey > node->key && node->right != nullptr) {
            node = node->right;
        } else {
            return false;
        }
    }
    int amount = node->childs();
    if(amount == 0) {
        deleteWithoutChild(node);
    } else if(amount == 1) {
        deleteWithOneChild(node);
    } else if(amount == 2){

    }
}

void AvlTree::deleteWithoutChild(Node *remove) {
    if(remove->previous == nullptr) {
        head = nullptr;
    } else {
        Node* pre = remove->previous;
        if(remove == remove->previous->left) {
            pre->left = nullptr;
            if(pre->right == nullptr) {
                pre->balance = 0;
                upout(pre);
            } else {
                if(pre->right->childs() == 0) {
                    pre->balance = 1;
                } else {
                    Node * node = nullptr;
                    if(pre->right->balance == 1) {
                        node = rotL(pre);
                    } else {
                        node = rotRL(pre);
                    }
                    fixBalances(node);
                }
            }
        } else {
            if(remove == remove->previous->right) {
                pre->right = nullptr;
                if(pre->left == nullptr) {
                    pre->balance = 0;
                    upout(pre);
                } else {
                    if(pre->left->childs() == 0) {
                        pre->balance = 1;
                    } else {
                        Node * node = nullptr;
                        if(pre->left->balance == -1) {
                            node = rotR(pre);
                        } else {
                            node = rotLR(pre);
                        }
                        fixBalances(node);
                    }
                }
            }
        }
    }
    delete remove;
}

void AvlTree::fixBalances(Node *node) {

    //left side
    if(node->getChild(left)->childs() == 2) {
        node->getChild(left)->balance = 0;
    } else if(node->getChild(left)->right) {
        node->getChild(left)->balance = 1;
    } else if(node->getChild(left)->left) {
        node->getChild(left)->balance = -1;
    } else {
        node->getChild(left)->balance = 0;
    }

    //right side
    if(node->getChild(right)->childs() == 2) {
        node->getChild(right)->balance = 0;
    } else if(node->getChild(right)->right) {
        node->getChild(right)->balance = 1;
    } else if(node->getChild(right)->left) {
        node->getChild(right)->balance = -1;
    } else {
        node->getChild(right)->balance = 0;
    }

    if(node->left->childs() == 0 && node->right->childs() > 0) {
        node->balance = 1;
    } else if(node->left->childs() > 0 && node->right->childs() == 0) {
        node->balance = -1;
    } else {
        upout(node);
    }
}

void AvlTree::deleteWithOneChild(Node *node) {
    if(node->left == nullptr) {
        Node *tmp = node->right;
        node->key = tmp->key;
        node->left = nullptr;
        node->right = nullptr;
        node->balance = 0;
        if(node->previous) upout(node);
        delete tmp;
    } else {
        Node *tmp = node->left;
        node->key = tmp->key;
        node->left = nullptr;
        node->right = nullptr;
        node->balance = 0;
        if(node->previous) upout(node);
        delete tmp;
    }
}