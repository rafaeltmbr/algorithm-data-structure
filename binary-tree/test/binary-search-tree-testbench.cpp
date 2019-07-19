/*
    g++ binary-search-tree-testbench.cpp ../src/binary-search-tree.cpp -g -Wall -std=c++14 -o search.exe
*/

#include "../include/binary-search-tree.hpp"
#include <iostream>

using namespace std;

#define ASSERT(cond, msg)                                                             \
    {                                                                                 \
        if (cond) {                                                                   \
            std::cout << "#";                                                         \
        } else {                                                                      \
            std::cerr << "\n Test failed (" << __LINE__ << "): " << msg << std::endl; \
            exit(EXIT_FAILURE);                                                       \
        }                                                                             \
    }


int main()
{
    cout << "------------------ Binary Search Tree Testbench -------------------\n";
    BinarySearchTree bstree;
    cout << "------------------------ Testbench Succeed ------------------------" << endl;
}