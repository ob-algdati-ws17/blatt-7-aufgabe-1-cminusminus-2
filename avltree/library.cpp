#include "library.h"
#include <iostream>
#include <iomanip>

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
    Node *tmp = head;
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

AvlTree::Node* AvlTree::rotateLeft(Node* node) {

}

int AvlTree::height(Node* node) {
    if (node == nullptr) return 0;
    return 1 + max(height(node->left), height(node->right));
}

bool AvlTree::isBalanced(Node* node) {
    if (node == nullptr) return true;
    int heightLeft = height(node->left);
    int heightRight = height(node->right);
    return abs(heightLeft - heightRight) < 2 && (isBalanced(node->right) && isBalanced(node->left));
}

bool AvlTree::insert(int const newKey) {
    Node *insert = new Node(newKey);
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


