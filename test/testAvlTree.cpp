#include "testAvlTree.h"
#include <memory>

using namespace std;

TEST(AvlTreeTest, NewInsert) {
    AvlTree tree;
    EXPECT_TRUE(tree.insert(2));
}

TEST(AvlTreeTest, NewAndExistingInsert) {
    AvlTree tree;
    EXPECT_TRUE(tree.insert(2));
    EXPECT_FALSE(tree.insert(2));
    EXPECT_FALSE(tree.insert(2));
    EXPECT_TRUE(tree.insert(3));
    EXPECT_FALSE(tree.insert(3));

}

TEST(AvlTreeTest, SearchWhenThereIsNothing) {
    AvlTree tree;
    EXPECT_FALSE(tree.search(2));
    EXPECT_FALSE(tree.search(3));
    EXPECT_FALSE(tree.search(4));
    EXPECT_FALSE(tree.search(5));
}

TEST(AvlTreeTest, SearchNotExistingNode) {
    AvlTree tree;
    tree.insert(1);
    EXPECT_FALSE(tree.search(2));
    EXPECT_TRUE(tree.search(1));

}

TEST(AvlTreeTest, SearchExistingNode) {
    AvlTree tree;
    tree.insert(1);
    EXPECT_TRUE(tree.search(1));

}

TEST(AvlTreeTest, LeftRotate) {
    AvlTree tree;
    for (int i = 0; i < 30; i++) {
        tree.insert(i);
    }
    EXPECT_TRUE(tree.isBalanced());
}


TEST(AvlTreeTest, RightRotate) {
    AvlTree tree;
    for (int i = 30; i > 0; i--) {
        tree.insert(i);
    }
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, RightRotate2) {
    AvlTree tree;
    for (int i = 30; i > 0; i--) {
        tree.insert(i);
    }
    for (int i = 10; i > 0; i = i - 2) {
        tree.insert(i);
    }
    EXPECT_TRUE(tree.isBalanced());
}


TEST(AvlTreeTest, OperatorAdd){
    AvlTree tree;
    tree += 2;
    ASSERT_TRUE(tree.search(2));
}


TEST(AvlTreeTest, OperatorRemove){
    AvlTree tree;
    tree += 2;
    tree -= 2;
    ASSERT_FALSE(tree.search(2));
}

TEST(AvlTreeTest, RemoveItemNotExist){
    AvlTree tree;
    tree.insert(1);
    ASSERT_FALSE(tree.remove(0));
}


TEST(AvlTreeTest, RemoveItem0Childs) {
    AvlTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    ASSERT_TRUE(tree.remove(3));
}


TEST(AvlTreeTest, RemoveRoot) {
    AvlTree tree;
    for (int i = 30; i > 0; i--) {
        tree.insert(i);
    }
    tree.remove(15);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, RemoveNodeWith2Childs) {
    AvlTree tree;
    for (int i = 30; i > 0; i--) {
        tree.insert(i);
    }
    tree.remove(11);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, RemoveNode1Child) {
    AvlTree tree;
    for (int i = 26; i > 0; i--) {
        tree.insert(i);
    }
    tree.remove(2);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, RemoveEmptyTree) {
    AvlTree tree;
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, OperatorOutput){
    AvlTree tree;
    tree.insert(0);
}


TEST(AvlTreeTest, HugeBalanceTest) {
    AvlTree tree;
    tree += 1;
    tree += 2;
    tree += 5;
    tree += 4;
    EXPECT_TRUE(tree.isBalanced());
    tree += 10;
    tree += 25;
    EXPECT_FALSE(tree.remove(24));
    EXPECT_TRUE(tree.isBalanced());
    tree += 22;
    tree += 3;
    EXPECT_TRUE(tree.isBalanced());
    tree -= 3;
    tree -= 2;
    tree -= 1;
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, Remove2Childs) {
    AvlTree tree;
    tree += 1;
    tree += 2;
    tree += 3;
    tree.remove(2);
    EXPECT_TRUE(tree.search(3));
    EXPECT_TRUE(tree.search(1));
}