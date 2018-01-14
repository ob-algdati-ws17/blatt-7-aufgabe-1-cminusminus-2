#include <iostream>
#include "gtest/gtest.h"
#include "avltree/library.h"

using namespace std;

int main(int argc, char **argv) {
//    AvlTree tree;
//    tree += 1;
//    tree += 2;
//    tree += 3;
//    tree += 4;
//    tree += 12;
//    tree += 123;
//    cout << tree << endl;
//    return 0;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}