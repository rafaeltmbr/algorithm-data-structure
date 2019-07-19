/*
    g++ binary-tree-testbench.cpp ../src/binary-tree.cpp -g -Wall -std=c++14 -o tree.exe
*/

#include "../include/binary-tree.hpp"
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

#define FAMILY_TREE_SIZE 7

string familyTree[FAMILY_TREE_SIZE] = {
    "G", //                   G
    "A", //           ________|________
    "B" //            |               |
    "AL", //          A               B
    "AR", //      ____|____       ____|____
    "BL", //      |       |       |       |
    "BR", //      AL      AR      BL      BR
};

void assignValues(BinaryTree& bitree);
void testCopyConstructor(BinaryTree& bitree);
void testInsert(BinaryTree& bitree);
void testRemove(BinaryTree& bitree);

int main()
{
    cout << "---------------------- Binary Tree Testbench ----------------------\n";
    BinaryTree bitree;
    assignValues(bitree);
    testCopyConstructor(bitree);
    testInsert(bitree);
    testRemove(bitree);
    cout << "------------------------ Testbench Succeed ------------------------" << endl;
}

void assignValues(BinaryTree& bitree)
{
    cout << " Assign Values Test: ";

    ASSERT(bitree.getSize() == 0, "getSize() failed");
    ASSERT(bitree.insertLeft(nullptr, familyTree), "insertLeft() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), familyTree + 1), "insertLeft() failed");
    ASSERT(bitree.insertRight(bitree.getRoot(), familyTree + 2), "insertRight() failed");

    BitreeNode* temp;
    temp = bitree.getRoot()->left;
    ASSERT(bitree.insertLeft(temp, familyTree + 3), "insertLeft() failed");
    ASSERT(bitree.insertRight(temp, familyTree + 4), "insertRight() failed");

    temp = bitree.getRoot()->right;
    ASSERT(bitree.insertLeft(temp, familyTree + 5), "insertLeft() failed");
    ASSERT(bitree.insertRight(temp, familyTree + 6), "insertRight() failed");

    ASSERT(bitree.getData(bitree.getRoot()) == familyTree, "data mismatch");
    ASSERT(bitree.getData(bitree.getLeft(bitree.getRoot())) == familyTree + 1, "data mismatch");
    ASSERT(bitree.getData(bitree.getRight(bitree.getRoot())) == familyTree + 2, "data mismatch");

    ASSERT(bitree.getSize() == FAMILY_TREE_SIZE, "getSize() failed");

    cout << " PASSED\n";
}

void testCopyConstructor(BinaryTree& bitree)
{
    cout << " Copy Constructor Test: ";
    BinaryTree copy(bitree);
    ASSERT(copy.getSize() == bitree.getSize(), "getSize() failed");
    ASSERT(copy.getRoot()->data == bitree.getRoot()->data, "getRoot() failed");
    ASSERT(copy.getRoot() != bitree.getRoot(), "roots evaluate to the same address");
    ASSERT(copy.getRoot()->left != bitree.getRoot()->left, "roots->left evaluate to the same address");
    ASSERT(copy.getRoot()->right != bitree.getRoot()->right, "roots->right evaluate to the same address");
    ASSERT(copy.getRoot()->left->data == bitree.getRoot()->left->data, "data mismatch");
    ASSERT(copy.getRoot()->right->data == bitree.getRoot()->right->data, "data mismatch");

    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");
    ASSERT(copy.getSize() == FAMILY_TREE_SIZE, "getSize() failed");

    cout << " PASSED\n";
}

void testInsert(BinaryTree& bitree)
{
    cout << " Insert Test: ";
    ASSERT(bitree.getSize() == 0, "getSize() failed");

    ASSERT(bitree.getRoot() == nullptr, "getRoot() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), familyTree), "insertLeft() failed");
    ASSERT(bitree.getRoot()->data == familyTree, "data mismatch");

    ASSERT(bitree.getRoot()->left == nullptr, "getRoot()->left failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), familyTree + 1), "insertLeft() failed");
    ASSERT(bitree.getRoot()->left->data == familyTree + 1, "data mismatch");

    ASSERT(bitree.getRoot()->right == nullptr, "getRoot()->right failed");
    ASSERT(bitree.insertRight(bitree.getRoot(), familyTree + 2), "insertRight() failed");
    ASSERT(bitree.getRoot()->right->data == familyTree + 2, "data mismatch");

    ASSERT(bitree.getSize() == 3, "getSize() failed");
    cout << " PASSED\n";
}

void testRemove(BinaryTree& bitree)
{
    cout << " Remove Test: ";

    ASSERT(bitree.getSize() == 3, "getSize() failed");

    ASSERT(bitree.getRoot()->left->data == familyTree + 1, "data mismatch");
    ASSERT(bitree.removeLeft(bitree.getRoot()), "removeLeft() failed");
    ASSERT(bitree.getRoot()->left == nullptr, "getRoot()->left failed");

    ASSERT(bitree.getRoot()->right->data == familyTree + 2, "data mismatch");
    ASSERT(bitree.removeRight(bitree.getRoot()), "removeRight() failed");
    ASSERT(bitree.getRoot()->right == nullptr, "getRoot()->right failed");

    ASSERT(bitree.getRoot()->data == familyTree, "data mismatch");
    ASSERT(bitree.removeLeft(nullptr), "removeLeft() failed");
    ASSERT(bitree.getRoot() == nullptr, "getRoot() failed");

    ASSERT(bitree.getSize() == 0, "getSize() failed");
    cout << " PASSED\n";
}