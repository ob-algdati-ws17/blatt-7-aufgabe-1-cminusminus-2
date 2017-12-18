#ifndef AVLTREE_LIB_H
#define AVLTREE_LIB_H

#include <ostream>

using namespace std;

/// An self balancing avl tree.
/// Implementation logic taken from slides. Working without calculating or saving the height!
class AvlTree {
private:

    /// the two different types of childs.
    enum Child{
        left, right
    };
    /// The struct containing all information about a node.
    struct Node {
        ~Node();

        /// Creates a new node.
        Node(int const);

        /// Creates a new node with given left and right child.
        Node(int const, Node *, Node *);
        /// Gets the amount of child nodes.
        /// \return the amount of child nodes that are attached to this node.
        int childs() const;
        /// Gets the left or right child node depending on the parameter.
        /// \return the child. (May be nullptr!)
        Node *getChild(Child) const;
        /// The key of the node.
        int key;
        /// The current balance of the node (Shal only be between -1 and 1)
        int balance = 0;
        /// The left child. Nullptr if a leaf.
        Node *left = nullptr;
        /// The right child. Nullptr if a leaf.
        Node *right = nullptr;
        /// The previous node of the node. Nullptr if this node is the root.
        Node *previous = nullptr;


    };

    /// The root of the tree.
    Node *root = nullptr;

    /// Rotates the (sub)tree leftwards and returns the root of the new (sub)tree
    /// \return the root of the new rotated (sub)tree.
    Node* rotateLeft(Node*);

    /// Rotates the (sub)tree rightwards and returns the root of the new (sub)tree
    /// \return the root of the new rotated (sub)tree.
    Node* rotateRight(Node*);

    /// Rotates the (sub)tree leftwards and than rightwards and returns the root of the new (sub)tree
    /// \return the root of the new rotated (sub)tree.
    Node* rotateLeftRight(Node*);

    /// Rotates the (sub)tree rightwards and than leftwards and returns the root of the new (sub)tree
    /// \return the root of the new rotated (sub)tree.
    Node* rotateRightLeft(Node*);

    /// The (recursive) logic after inserting a node.
    void upin(Node*);

    /// The (recursive) logic after removing a node.
    void upout(Node*);

    /// Generates a human readable information about this node.
    void display(Node*, int);

    /// Calculates the total height of the node's subtree.
    /// \return the height of the subtree.
    int height(Node*);

    /// Checks if the node is balanced.
    /// \return true if balanced, otherwise false.
    bool isBalanced(Node*);

    /// Deletes a node from the tree without any child
    void deleteWithoutChild(Node*);

    /// Deletes a node from the tree with one child.
    void deleteWithOneChild(Node*);

    /// Fixes balances after deleting a node.
    void fixBalancesDelete(Node*);

    /// Fixes balaces of the left or right sub node after deleting a node.
    void fixBalancesChild(const Node*, Child) const;

public:

    /// Destructor for the tree. Deletes also all nodes
    ~AvlTree();

    /// Searches for a node in the tree.
    /// \return true if found, false if not.
    bool search(int const) const;

    /// Inserts a new node into the tree.
    /// \return true if node was inserted, false if not (Already exists)
    bool insert(int const);

    /// Removes a node in the tree.
    /// \return true if it was removed, false if not (not found)
    bool remove(int const);

    /// Add operator
    /// \return a tree with the new key inserted.
    friend AvlTree &operator+=(AvlTree &, int const);

    /// Remove operator
    /// \return a tree without the key to delete.
    friend AvlTree &operator-=(AvlTree &, int const);

    /// Outputs the tree.
    /// \return the stream containing the output information.
    friend ostream &operator<<(ostream &, AvlTree &);

    /// Displays the tree on the console. Only for testing and debug purpose. Performance is aweful!
    void display();

    /// Tests whether the tree is balanced (or not). Only for testing and debug purpose. Performance is aweful!
    /// \return true if balanced, otherwise false.
    bool isBalanced();

};

#endif