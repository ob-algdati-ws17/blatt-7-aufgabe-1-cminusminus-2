#ifndef AVLTREE_LIB_H
#define AVLTREE_LIB_H

#include <ostream>

using namespace std;

class AvlTree {
private:
    struct Node {
        ~Node();
        Node(int const);
        Node(int const, Node *, Node *);

        int childs() const;
        int key;
        int bal = 0;

        Node *left = nullptr;
        Node *right = nullptr;
        Node *previous = nullptr;
    };


    Node *head = nullptr;

    /*
     * Rotates the (sub)tree leftwards and returns the root of the new (sub)tree
     * return the root of the new rotated (sub)tree.
     */
    Node* rotL(Node*);

    /*
     * Rotates the (sub)tree rightwards and returns the root of the new (sub)tree
     * return the root of the new rotated (sub)tree.
     */
    Node* rotR(Node*);

    /*
     * Rotates the (sub)tree leftwards and than rightwards and returns the root of the new (sub)tree
     * return the root of the new rotated (sub)tree.
     */
    Node* rotLR(Node*);
    /*
     * Rotates the (sub)tree rightwards and than leftwards and returns the root of the new (sub)tree
     * return the root of the new rotated (sub)tree.
     */

    Node* rotRL(Node*);

    /* logic after inserting a node. */
    void upin(Node*);

    /* logic after removing a node. */
    void upout(Node*);

    /*
     * Calculates the total height of the node's subtree.
     * return the height of the subtree.
     */
    int height(Node*);

    /*
     * Checks if the node is balanced.
     * return true if balanced, otherwise false.
     */
    bool isBalanced(Node*);

    /* Fixes balances after deleting a node. */
    void fixBalances(Node *);

    /* Node has no child. */
    void deleteNoChild(Node *);

    /* Node has a child. */
    void deleteOneChild(Node *);

public:

    /* Destructor for the tree. Deletes also all nodes */
    ~AvlTree();

    /*
     * Searches for a node in the tree.
     * return true if found.
     */
    bool search(int const) const;

    /*
     * Inserts a new node into the tree.
     * return true if node was inserted, false if not (Already exists)
     */
     bool insert(int const);

    /*
     * Removes a node in the tree.
     * return true if it was removed, false if not (not found)
     */
     bool remove(int const);

    /*
     * Add operator
     * return a tree with the new key inserted.
     */
    friend AvlTree &operator+=(AvlTree &, int const);

    /*
     * Remove operator
     *return a tree without the key to delete.
     */
    friend AvlTree &operator-=(AvlTree &, int const);

    /*
     * Outputs the tree.
     * return the stream containing the output information.
     */
     friend ostream  &operator<<(ostream &, AvlTree &);

    /*
     * Tests whether the tree is balanced (or not). Only for testing and debug purpose. Performance is aweful!
     * return true if balanced, otherwise false.
     */
    bool isBalanced();

    /*
     * calls show(AvlTree::Node*, int) with the head.
     */
    void show();

    /*
     * creates recursive a tree on the console.
     */
    void show(AvlTree::Node*, int);

};

#endif