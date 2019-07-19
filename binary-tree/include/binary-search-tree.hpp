#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "binary-tree.hpp"

typedef int (*compare_t)(const void* data1, const void* data2);

class BitreeSNode : public BitreeNode {
public:
    bool visible = true;
    int balance = 0;
    BitreeSNode(void *data): BitreeNode(data) {}
};

class BinarySearchTree : public BinaryTree {
protected:
    compare_t compare;

public:
    bool insert(void* data);
    bool remove(void* data);
    void* lookup(void* data);
    bool insertLeft(BitreeNode* node, void* data) = delete;
    bool insertRight(BitreeNode* node, void* data) = delete;
    bool removeLeft(BitreeNode* node) = delete;
    bool removeRight(BitreeNode* node) = delete;
};

#endif // BINARY_SEARCH_TREE_HPP