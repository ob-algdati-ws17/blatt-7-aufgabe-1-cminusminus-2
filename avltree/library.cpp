#include "library.h"
#include <iomanip>
#include <iostream>

using namespace std;

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

/*
 * returns true if the key already exists
 */
bool AvlTree::search(int const key) const {
    auto tmp = head;
    while (tmp != nullptr) {
        if (key == tmp->key) return true;
        if (key < tmp->key) tmp = tmp->left;
        else tmp = tmp->right;
    }
    /*
     * If there no "key" found in the tree
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
    node->bal = 0;
    r->bal = 0;
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
    l->bal = 0;
    node->bal = 0;
    return l;
};

/*
 * Case: Rotate Right, Left
 */
AvlTree::Node *AvlTree::rotRL(AvlTree::Node *node) {
    auto tmp = node->right->left;
    bool lessThanLeft = true;
    if (tmp->bal == -1) lessThanLeft = false;
    rotR(node->right);
    auto reTurn = rotL(node);
    if (!lessThanLeft && reTurn->right->childs() != 0) reTurn->left->bal = -1;
    else if (lessThanLeft && reTurn->left->childs() != 0) reTurn->right->bal = 1;
    return reTurn;
};

/*
 * Case: Rotate Left, Right
 */
AvlTree::Node *AvlTree::rotLR(AvlTree::Node *node) {
    auto tmp = node->left->right;
    bool lessThanRight = true;
    if (tmp->bal == -1) lessThanRight = false;
    rotL(node->left);
    auto reTurn = rotR(node);
    if (lessThanRight && reTurn->left->childs() != 0) reTurn->left->bal = -1;
    else if ( !lessThanRight && reTurn->right->childs() != 0) reTurn->right->bal = 1;
    return reTurn;
};

int AvlTree::height(AvlTree::Node* node) {
    if (node == nullptr) return 0;
    return max(height(node->left), height(node->right)) + 1;
}

bool AvlTree::isBalanced() {
    isBalanced(head);
}

/*
 * returns true if the height of the tree is max 1 node bigger/smaller than others
 */
bool AvlTree::isBalanced(Node* node) {
    if (node == nullptr) return true;
    int heightLeft = height(node->left);
    int heightRight = height(node->right);
    return abs(heightLeft - heightRight) < 2 && (isBalanced(node->right) && isBalanced(node->left));
}

bool AvlTree::insert(int const newKey) {
    /*
     * wenn der head noch nicht existiert, wird der erste Key der Head.
     */
    auto insert = new Node(newKey);
    if (head == nullptr) {
        head = insert;
        return true;
    }

    auto tmp = head;
    bool insertNow = true;
    /*
     * Solange die neue Stelle der Zahl nicht gefunden wurde,
     * durchlaufe den Baum. tmp steht dann an der richtigen Stelle.
     * tmp steht dann an dem Node, wo die isnert-Zahl drangehängt wird.
     */
    while (insertNow) {
        if (newKey > tmp->key && tmp->right) tmp = tmp->right;
        else if (newKey < tmp->key && tmp->left) tmp = tmp->left;
        else insertNow = false;
    }
    /*
     * hänge die Zahl an tmp an.
     */
    insert->previous = tmp;
    if (newKey > tmp->key) {
        tmp->right = insert;
        tmp->bal += 1;
    } else if (newKey < tmp->key) {
        tmp->left = insert;
        tmp->bal -= 1;
    }
    /*
     * Wenn der bal verloren gegangen ist, balanciere mit upin erneut.
     */
    if (tmp->bal != 0) {
        upin(tmp);
    }
}

void AvlTree::upin(AvlTree::Node *node) {
    /* */
    if (node != nullptr && node->previous != nullptr) {
        auto prev = node->previous;
        if (node == prev->left) {
            if (prev->bal == -1 && node->bal == -1) rotR(prev);
            else if (prev->bal == -1 && node->bal == 1) rotLR(prev);
            else if (prev->bal == 1) prev->bal = 0;
            else if (prev->bal == 0) {
                prev->bal = -1;
                upin(prev);
            }
            return;
        } else {
            if (prev->bal == 1 && node->bal == -1) rotRL(prev);
            else if (prev->bal == 1 && node->bal == 1) rotL(prev);
            else if (prev->bal == -1) prev->bal = 0;
                else if (prev->bal == 0) {
                prev->bal = 1;
                upin(prev);
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
            if (node->previous->bal == -1) {
                node->previous->bal = 0;
                upout(node->previous);
            } else if (node->previous->bal == 0) {
                node->previous->bal = 1;
                return;
            } else {
                if (node->previous->right->bal == 0) {
                    auto newRoot = rotL(node->previous);
                    newRoot->bal = -1;
                    newRoot->left->bal = 1;
                    newRoot->left->left->bal = 0;
                } else if (node->previous->right->bal == 1) {
                    Node *newRoot = rotL(node->previous);
                    newRoot->bal = 0;
                    newRoot->left->bal = 0;
                    newRoot->left->left->bal = 0;
                } else {
                    int oldQbal = node->previous->right->left->bal;
                    auto newRoot = rotRL(node->previous);
                    newRoot->bal = 0;
                    newRoot->left->left->bal = 0;
                    newRoot->right->bal = 0;
                    newRoot->left->bal = 0;
                    if(oldQbal == 1) newRoot->left->bal = -1;
                    else if(oldQbal == -1) newRoot->right->bal = 1;
                    upout(newRoot);
                }
            }

            //right side

        }else {
            if (node->previous->right == node) {
                if (node->previous->bal == -1) {
                    node->previous->bal = 0;
                    upout(node->previous);
                } else if (node->previous->bal == 0) {
                    node->previous->bal = 0;
                    return;
                } else {
                    if (node->previous->left->bal == 0) {
                        Node *newRoot = rotR(node->previous);
                        newRoot->bal = -1;
                        newRoot->right->bal = 1;
                        newRoot->right->right->bal = 0;
                    } else if (node->previous->left->bal == 1) {
                        Node *newRoot = rotR(node->previous);
                        newRoot->bal = 0;
                        newRoot->right->bal = 0;
                        newRoot->right->right->bal = 0;
                    } else {
                        //Doppelrotation links-rechts
                        //fehlt noch newRoot->left / right -> bal;
                        int oldQbal = node->previous->left->right->bal;
                        Node *newRoot = rotLR(node->previous);
                        newRoot->bal = 0;
                        newRoot->right->right->bal = 0;
                        newRoot->right->bal = 0;
                        newRoot->left->bal = 0;
                        if(oldQbal == 1) {
                            newRoot->left->bal = -1;
                        } else if(oldQbal == -1) {
                            newRoot->right->bal = 1;
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
        if(removeKey == node->key) break;
        else if(removeKey < node->key && node->left != nullptr) {
            node = node->left;
        } else if(removeKey > node->key && node->right != nullptr) {
            node = node->right;
        } else return false;
    }
    int amount = node->childs();
    if (amount == 0) deleteWithoutChild(node);
    else if (amount == 1) deleteWithOneChild(node);
}

void AvlTree::deleteWithoutChild(Node *remove) {
    if (remove->previous == nullptr) {
        head = nullptr;
    } else {
        auto pre = remove->previous;
        if (remove == remove->previous->left) {
            pre->left = nullptr;
            if(pre->right == nullptr) {
                pre->bal = 0;
                upout(pre);
            } else {
                if (pre->right->childs() == 0) {
                    pre->bal = 1;
                } else {
                    Node *node = nullptr;
                    if(pre->right->bal == 1) {
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
                    pre->bal = 0;
                    upout(pre);
                } else {
                    if(pre->left->childs() == 0) {
                        pre->bal = 1;
                    } else {
                        Node *node = nullptr;
                        if(pre->left->bal == -1) {
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
    if (node->left->childs() == 2) node->left->bal = 0;
    else if(node->left->right) node->left->bal = 1;
    else if(node->left->left) node->left->bal = -1;
    else node->left->bal = 0;

    //right side
    if (node->right->childs() == 2) node->right->bal = 0;
    else if(node->right->right) node->right->bal = 1;
    else if(node->right->left) node->right->bal = -1;
    else node->right->bal = 0;

    if (node->left->childs() == 0 && node->right->childs() > 0)
        node->bal = 1;
    else if (node->left->childs() > 0 && node->right->childs() == 0)
        node->bal = -1;
    else upout(node);
}

void AvlTree::deleteWithOneChild(Node *node) {
    if (node->left == nullptr) {
        auto tmp = node->right;
        node->key = tmp->key;
        node->left = nullptr;
        node->right = nullptr;
        node->bal = 0;
        if (node->previous) upout(node);
        delete tmp;
    } else {
        auto tmp = node->left;
        node->key = tmp->key;
        node->left = nullptr;
        node->right = nullptr;
        node->bal = 0;
        if (node->previous) upout(node);
        delete tmp;
    }
}

void AvlTree::show() {
    show(head, 0);
}

void AvlTree::show(AvlTree::Node *node, int offset) {
    if (node != nullptr) {
        show(node->right, offset + 5);
        if (offset > 0) cout << setw(offset) << " ";
        cout << node->key << endl;
        show(node->left, offset + 5);
    }
}

ostream &operator<<(ostream &stream, AvlTree &tree) {
    tree.show();
    return cout;
};
