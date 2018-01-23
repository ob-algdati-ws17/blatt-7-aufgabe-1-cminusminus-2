#include "testAvlTree.h"
#include <memory>

using namespace std;

TEST(AvlTreeTest, remove_Check) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(8);
    tree.insert(17);
    tree.insert(7);
    tree.insert(19);
    tree.remove(17);
    ASSERT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, remove_check) {
    AvlTree tree;
    tree.insert(15);
    tree.insert(10);
    tree.insert(12);
    tree.insert(17);
    tree.insert(20);
    tree.insert(7);
    tree.insert(5);
    tree.remove(20);
    ASSERT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, remove_leaf) {
    AvlTree tree;
    tree.insert(15);
    tree.insert(10);
    tree.insert(18);
    tree.insert(7);
    tree.insert(12);
    tree.insert(8);
    tree.insert(20);
    tree.remove(8);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, remove10) {
    AvlTree tree;
    tree.insert(15);
    tree.insert(10);
    tree.insert(20);
    tree.insert(25);
    tree.insert(9);
    tree.insert(14);
    tree.insert(8);
    tree.show();
    tree.remove(25);
    tree.remove(10);
    tree.show();
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, remove_l) {
    AvlTree tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(35);
    tree.insert(40);
    tree.insert(31);
    tree.insert(8);
    tree.show();
    cout << "\n" << endl;
    tree.insert(2);
    tree.show();
    cout << "\n" << endl;
    tree.remove(31);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, removeTester) {
    AvlTree tree;
    tree.insert(15);
    tree.insert(12);
    tree.insert(20);
    tree.insert(25);
    tree.insert(16);
    tree.insert(7);
    tree.insert(28);
    tree.remove(7);
    EXPECT_TRUE(tree.isBalanced());
}


TEST(AvlTreeTest, remove_leaft) {
    AvlTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(30);
    tree.insert(22);
    tree.insert(15);
    tree.insert(17);
    tree.show();
    tree.remove(30);
    tree.remove(22);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, removetest) {
    AvlTree tree;
    tree.insert(15);
    tree.insert(10);
    tree.insert(18);
    tree.insert(7);
    tree.insert(12);
    tree.insert(8);
    tree.show();
    tree.insert(20);
    tree.show();
    tree.remove(8);
    tree.remove(18);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, remove_leaf1) {
    AvlTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(30);
    tree.insert(22);
    tree.insert(15);
    tree.insert(17);
    tree.show();
    tree.remove(22);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, remove_leaf2) {
    AvlTree tree;
    tree.insert(20);
    tree.insert(25);
    tree.insert(10);
    tree.insert(7);
    tree.insert(12);
    tree.insert(21);
    tree.show();
    tree.remove(21);
    EXPECT_TRUE(tree.isBalanced());
}



TEST(AvlTreeTest, remove) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(12);
    tree.insert(7);
    tree.insert(5);
    tree.insert(9);
    tree.insert(14);
    tree.insert(11);
    EXPECT_TRUE(tree.isBalanced());
}


TEST(AvlTreeTest,INSERT_RIGHT_LEFT_ROTATION) {
    AvlTree tree;
    tree.insert(5);
    tree.insert(6);
    tree.insert(13);
    tree.insert(12);
    tree.insert(11);
    tree.insert(10);
    ASSERT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest,INSERT_LEFT_RIGHT_ROTATION) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(7);
    tree.insert(2);
    tree.insert(6);
    ASSERT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest,CheckTest) {
    AvlTree tree;
    for(int i = 0; i < 20; i++) {
        tree.insert(i);
    }
    tree.remove(20);
    tree.remove(17);
    tree.remove(8);
    ASSERT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, Remove_RotateLeftRight) {
    AvlTree tree;
    tree += 20;
    tree += 10;
    tree += 30;
    tree += 15;
    tree += 5;
    tree += 40;
    tree += 2;
    tree += 7;
    tree -= 15;
    ASSERT_TRUE(tree.isBalanced());
}

TEST(AvlTreeTest, Remove_RotateRechtsLinks) {
    AvlTree tree;
    tree += 20;
    tree += 25;
    tree += 15;
    tree += 5;
    tree += 40;
    tree += 22;
    tree += 38;
    tree += 45;
    tree -= 22;
    ASSERT_TRUE(tree.isBalanced());
}


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