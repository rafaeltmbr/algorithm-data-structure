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
    "B", //           |               |
    "AL", //          A               B
    "AR", //      ____|____       ____|____
    "BL", //      |       |       |       |
    "BR", //      AL      AR      BL      BR
};

void assignFamilyTree(BinaryTree& bitree);
void testCopyConstructor(BinaryTree& bitree);
void testInsert(BinaryTree& bitree);
void testRemove(BinaryTree& bitree);
void testMerge(BinaryTree& bitree);
void testScanPreorder(BinaryTree& bitree);
void testScanInorder(BinaryTree& bitree);
void testScanPostorder(BinaryTree& bitree);
void testDestroy(BinaryTree& bitree);

int main()
{
    cout << "---------------------- Binary Tree Testbench ----------------------\n";
    BinaryTree bitree;
    testCopyConstructor(bitree);
    testInsert(bitree);
    testRemove(bitree);
    testMerge(bitree);
    testScanPreorder(bitree);
    testScanInorder(bitree);
    testScanPostorder(bitree);
    testDestroy(bitree);
    cout << "------------------------ Testbench Succeed ------------------------" << endl;
}

void assignFamilyTree(BinaryTree& bitree)
{
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
}

void testCopyConstructor(BinaryTree& bitree)
{
    cout << " Copy Constructor Test: ";

    ASSERT(bitree.getSize() == 0, "getSize() failed");
    assignFamilyTree(bitree);
    ASSERT(bitree.getSize() == FAMILY_TREE_SIZE, "getSize() failed");

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

void testMerge(BinaryTree& bitree)
{
    cout << " Merge Test: ";
    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");

    int i1[] = { 10, 11, 12 };
    int i2[] = { 20, 21, 22 };

    BinaryTree t1, t2;
    ASSERT(t1.insertLeft(t1.getRoot(), i1), "insertLeft() failed");
    ASSERT(t1.insertLeft(t1.getRoot(), i1 + 1), "insertLeft() failed");
    ASSERT(t1.insertRight(t1.getRoot(), i1 + 2), "insertRight() failed");
    ASSERT(t1.getSize() == 3, "getSize() failed");

    ASSERT(t2.insertRight(t2.getRoot(), i2), "insertRight() failed");
    ASSERT(t2.insertLeft(t2.getRoot(), i2 + 1), "insertLeft() failed");
    ASSERT(t2.insertRight(t2.getRoot(), i2 + 2), "insertRight() failed");
    ASSERT(t2.getSize() == 3, "getSize() failed");

    ASSERT(bitree.merge(t1, t2), "merge() failed");
    ASSERT(bitree.getSize() == (t1.getSize() + t2.getSize() + 1), "getSize() failed");
    ASSERT(bitree.getRoot()->data == nullptr, "getRoot()->data failed");

    ASSERT(t1.getSize() == 3, "getSize() failed");
    ASSERT(t2.getSize() == 3, "getSize() failed");
    t1.destroy();
    t2.destroy();
    ASSERT(t1.getSize() == 0, "getSize() failed");
    ASSERT(t2.getSize() == 0, "getSize() failed");
    ASSERT(bitree.getSize() == 7, "getSize() failed");

    BitreeNode* temp = bitree.getRoot()->left;
    ASSERT(temp->data == i1, "data mismatch");
    ASSERT(temp->left->data == i1 + 1, "data mismatch");
    ASSERT(temp->right->data == i1 + 2, "data mismatch");

    temp = bitree.getRoot()->right;
    ASSERT(temp->data == i2, "data mismatch");
    ASSERT(temp->left->data == i2 + 1, "data mismatch");
    ASSERT(temp->right->data == i2 + 2, "data mismatch");

    cout << " PASSED\n";
}

void testScanPreorder(BinaryTree& bitree)
{
    cout << " Scan Preorder Test: ";
    static int test[] = { 1, 2, 3 };
    static int ans[] = { 1, 2, 3 };
    static int i = 0;

    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), test), "insertLeft() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), test + 1), "insertLeft() failed");
    ASSERT(bitree.insertRight(bitree.getRoot(), test + 2), "insertRight() failed");
    ASSERT(bitree.getSize() == 3, "getSize() failed");

    bitree.scanPreorder([](BitreeNode* n) {
        ASSERT(*((int*)n->data) == ans[i], "scanPreorder() failed in loop: " << i);
        i++;
    });

    ASSERT(bitree.getSize() == 3, "getSize() failed");
    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");
    cout << " PASSED\n";
}

void testScanInorder(BinaryTree& bitree)
{
    cout << " Scan Inorder Test: ";
    static int test[] = { 1, 2, 3 };
    static int ans[] = { 2, 1, 3 };
    static int i = 0;

    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), test), "insertLeft() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), test + 1), "insertLeft() failed");
    ASSERT(bitree.insertRight(bitree.getRoot(), test + 2), "insertRight() failed");
    ASSERT(bitree.getSize() == 3, "getSize() failed");

    bitree.scanInorder([](BitreeNode* n) {
        ASSERT(*((int*)n->data) == ans[i], "scanInorder() failed in loop: " << i);
        i++;
    });

    ASSERT(bitree.getSize() == 3, "getSize() failed");
    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");
    cout << " PASSED\n";
}

void testScanPostorder(BinaryTree& bitree)
{
    cout << " Scan Postorder Test: ";
    static int test[] = { 1, 2, 3 };
    static int ans[] = { 2, 3, 1 };
    static int i = 0;

    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), test), "insertLeft() failed");
    ASSERT(bitree.insertLeft(bitree.getRoot(), test + 1), "insertLeft() failed");
    ASSERT(bitree.insertRight(bitree.getRoot(), test + 2), "insertRight() failed");
    ASSERT(bitree.getSize() == 3, "getSize() failed");

    bitree.scanPostorder([](BitreeNode* n) {
        ASSERT(*((int*)n->data) == ans[i], "scanPostorder() failed in loop: " << i);
        i++;
    });

    ASSERT(bitree.getSize() == 3, "getSize() failed");
    bitree.destroy();
    ASSERT(bitree.getSize() == 0, "getSize() failed");
    cout << " PASSED\n";
}

void testDestroy(BinaryTree& bitree)
{
    cout << " Destroy test: ";

    bitree.destroy();
    assignFamilyTree(bitree);
    ASSERT(bitree.getSize() == FAMILY_TREE_SIZE, "getSize() failed");

    static string s = "";
    bitree.destroy([](void* d) {
        s += *(string*)d;
    });

    ASSERT(s == "ALARABLBRBG", "destroy() failed");
    ASSERT(bitree.getSize() == 0, "getSize() failed");

    cout << " PASSED\n";
}