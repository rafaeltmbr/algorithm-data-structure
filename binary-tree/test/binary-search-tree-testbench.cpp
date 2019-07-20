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

void testInsertLookupRemove(BinarySearchTree& bstree);
void testConstructor(BinarySearchTree& bstree);
int compareInt(const void* data1, const void* data2)
{
    return (*(int*)data1) - (*(int*)data2);
}

int main()
{
    cout << "------------------ Binary Search Tree Testbench -------------------\n";
    BinarySearchTree bstree;
    testConstructor(bstree);
    testInsertLookupRemove(bstree);
    cout << "------------------------ Testbench Succeed ------------------------" << endl;
}

void testConstructor(BinarySearchTree& bstree)
{
    cout << " Constructor Test: ";

    const int iSize = 5;
    int i[] = { 0, -1, -2, 1, 2 };

    bstree.setCompare(compareInt);
    ASSERT(bstree.getSize() == 0, "getSize() failed");
    for (int j = 0; j < iSize; j++)
        ASSERT(bstree.insert(i + j), "insert() failed in loop: " << j);
    ASSERT(bstree.getSize() == iSize, "getSize() failed");

    BinarySearchTree copy(bstree);

    ASSERT(copy.getSize() == iSize, "getSize() failed");
    for (int j = 0; j < iSize; j++)
        ASSERT(copy.lookup(i + j), "lookup() failed in loop: " << j);

    bstree.destroy();
    ASSERT(bstree.getSize() == 0, "getSize() failed");
    ASSERT(copy.getSize() == iSize, "getSize() failed");

    cout << " PASSED\n";
}

void testInsertLookupRemove(BinarySearchTree& bstree)
{
    cout << " Insert, Lookup and Remove Test: ";

    const int iSize = 5;
    int i[iSize] = { 0, 1, -1, 2, -2 };
    ASSERT(bstree.getSize() == 0, "getSize() failed");
    bstree.setCompare(compareInt);

    for (int j = 0; j < iSize; j++)
        ASSERT(bstree.insert(i + j), "insert() failed in loop: " << j);
    ASSERT(bstree.getSize() == iSize, "getSize() failed");

    for (int j = 0; j < iSize; j++)
        ASSERT(!bstree.insert(i + j), "insert() failed in loop: " << j);
    ASSERT(bstree.getSize() == iSize, "getSize() failed");

    for (int j = 0; j < iSize; j++)
        ASSERT(bstree.lookup(i + j), "lookup() failed in loop: " << j);
    ASSERT(bstree.getSize() == iSize, "getSize() failed");

    for (int j = 0; j < iSize; j++)
        ASSERT(bstree.remove(i + j), "remove() failed in loop: " << j);
    ASSERT(bstree.getSize() == iSize, "getSize() failed");

    for (int j = 0; j < iSize; j++)
        ASSERT(!bstree.lookup(i + j), "lookup() failed in loop: " << j);
    ASSERT(bstree.getSize() == iSize, "getSize() failed");

    bstree.destroy();
    ASSERT(bstree.getSize() == 0, "getSize() failed");
    cout << " PASSED\n";
}
