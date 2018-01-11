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
