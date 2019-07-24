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
void testInsertDeleteBranch(BinarySearchTree& bstree);
void testDestroy(BinarySearchTree& bstree);
int compareInt(const void* data1, const void* data2);
void testBalance(BinarySearchTree& bstree);

int main()
{
    cout << "------------------ Binary Search Tree Testbench -------------------\n";
    BinarySearchTree bstree;
    testConstructor(bstree);
    testInsertLookupRemove(bstree);
    testInsertDeleteBranch(bstree);
    testDestroy(bstree);
    testBalance(bstree);
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

void testInsertDeleteBranch(BinarySearchTree& bstree)
{
    cout << " Insert and Delete Branch Test: ";
    const int iSize1 = 7;
    const int iSize2 = 4;
    //const int iSize3 = 3;

    int i1[iSize1] = { 0, -1, -2, -3, 1, 2, 3 };
    int i2[iSize2] = { 0, 2, 4, 6 };

    bstree.setCompare(compareInt);
    ASSERT(bstree.getSize() == 0, "getSize() failed");
    for (int i = 0; i < iSize1; i++)
        ASSERT(bstree.insert(i1 + i), "insert() failed in loop: " << i);
    ASSERT(bstree.getSize() == iSize1, "getSize() failed");

    BinarySearchTree evenTree(compareInt);
    for (int i = 0; i < iSize2; i++)
        ASSERT(evenTree.insert(i2 + i), "insert() failed in loop: " << i);
    ASSERT(evenTree.getSize() == iSize2, "getSize() failed");

    ASSERT(bstree.insertBranch(evenTree.getRoot()), "insertBranch() failed");
    ASSERT(bstree.getSize() == 9, "getSize() failed");
    for (int i = 0; i < iSize2; i++)
        ASSERT(bstree.lookup(i2 + i), "lookup() failed in loop: " << i);

    ASSERT(bstree.deleteBranch(i1+1), "deleteBranch() failed");
    ASSERT(bstree.getSize() == 0, "getSize failed: ");

    cout << " PASSED\n";
}

void testDestroy(BinarySearchTree& bstree)
{
    cout << " Destroy Test: ";
    string s[] = { "Congratulations", "Test", "Succeed" };

    ASSERT(bstree.getSize() == 0, "getSize() failed");

    bstree.setCompare([](const void* d1, const void* d2) {
        string s1 = *(string*)d1;
        string s2 = *(string*)d2;
        return s1 == s2 ? 0
                        : s1 > s2 ? 1
                                  : -1;
    });
    static string ans;
    bstree.setDestroy([](void* s) {
        ans += *(string*)s + " ";
    });

    ASSERT(bstree.insert(s + 2), "insert() failed");
    ASSERT(bstree.insert(s + 1), "insert() failed");
    ASSERT(bstree.insert(s), "insert() failed");
    ASSERT(bstree.getSize() == 3, "getSize() failed");

    ASSERT(ans.length() == 0, "ans must be empty");
    bstree.destroy();
    ASSERT(ans == "Congratulations Test Succeed ", "destroy() failed: ");
    ASSERT(bstree.getSize() == 0, "getSize() failed");

    cout << " PASSED\n";
}

void testBalance(BinarySearchTree& bstree)
{
    cout << " Balance Test: ";
    bstree.setCompare(compareInt);

    ASSERT(bstree.getSize() == 0, "getSize() failed");
    const int pSize = 9;
    int p[pSize] = { 20, 10, 0, 30, 40, -20, -10, 25, 22};
    int expectedHeightP[pSize] = {1, 2, 2, 3, 3, 3, 3, 4, 4};

    for (int i = 0; i < pSize; i++) {
        bstree.insert(p + i);
        ASSERT(bstree.getHeight() == expectedHeightP[i], "getHeight() failed in loop: " << i);
    }
    ASSERT(bstree.getSize() == pSize, "getSize() failed");

    cout << " PASSED\n";
}

int compareInt(const void* data1, const void* data2)
{
    return (*(int*)data1) - (*(int*)data2);
}
