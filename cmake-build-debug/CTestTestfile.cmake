# CMake generated Testfile for 
# Source directory: C:/Users/Nam Pham/CLionProjects/blatt-7-aufgabe-1-cminusminus-2
# Build directory: C:/Users/Nam Pham/CLionProjects/blatt-7-aufgabe-1-cminusminus-2/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(testAvlTree "test/testAvlTree" "--gtest_output=xml:report.xml")
subdirs("avltree")
subdirs("googletest-build")
subdirs("test")
