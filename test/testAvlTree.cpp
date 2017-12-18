#include "testAvlTree.h"
#include <memory>

using namespace std;

TEST(AvlTreeTest, Insert_Not_Exists) {
    AvlTree tree;
    EXPECT_TRUE(tree.insert(2));
}

TEST(AvlTreeTest, Insert_Exists) {
    AvlTree tree;
    EXPECT_TRUE(tree.insert(2));
    EXPECT_FALSE(tree.insert(2));
}

TEST(AvlTreeTest, Search_Empty) {
    AvlTree tree;
    EXPECT_FALSE(tree.search(2));
}

TEST(AvlTreeTest, Search_Not_Exists) {
    AvlTree tree;
    tree.insert(1);
    EXPECT_FALSE(tree.search(2));
}

TEST(AvlTreeTest, Search_Exists) {
    AvlTree tree;
    tree.insert(1);
    EXPECT_TRUE(tree.search(1));

}

TEST(AvlTreeTest, Insert_LeftRotateForce) {
    AvlTree tree;
    for (int i = 1; i <= 30; i++) {
        tree.insert(i);
    }
    EXPECT_TRUE(tree.isBalanced());
}


TEST(AvlTreeTest, Insert_RightRotateForce) {
    AvlTree tree;
    for (int i = 30; i > 0; i--) {
        tree.insert(i);
    }
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, Remove_Root) {
    AvlTree tree;
    for (int i = 30; i > 0; i--) {
        tree.insert(i);
    }
    tree.remove(15);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, Remove_Node_2Childs) {
    AvlTree tree;
    for (int i = 30; i > 0; i--) {
        tree.insert(i);
    }
    tree.remove(11);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, Remove_Node_1Childs) {
    AvlTree tree;
    for (int i = 26; i > 0; i--) {
        tree.insert(i);
    }
    tree.remove(2);
    EXPECT_TRUE(tree.isBalanced());
}



TEST(AvlTreeTest, RemoveEmptyTree) {
    AvlTree tree;
    ASSERT_FALSE(tree.remove(0));
}

TEST(AvlTreeTest, RemoveItem0Childs) {
    AvlTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    ASSERT_TRUE(tree.remove(3));
}

TEST(AvlTreeTest, RemoveItemNotExist){
    AvlTree tree;
    tree.insert(1);
    ASSERT_FALSE(tree.remove(0));
}

TEST(AvlTreeTest, OperatorOutput){
    AvlTree tree;
    tree.insert(0);
    cout << tree;
}


TEST(AvlTreeTest, OperatorRemove){
    AvlTree tree;
    tree += 2;
    tree -= 2;
    ASSERT_FALSE(tree.search(2));
}

TEST(AvlTreeTest, OperatorAdd){
    AvlTree tree;
    tree += 2;
    ASSERT_TRUE(tree.search(2));
}