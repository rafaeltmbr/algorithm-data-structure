#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <string>

class BitreeNode;
class BinaryTree;

typedef void (*destroy_t)(void* data);
typedef void (*callback_t)(BitreeNode* node);
typedef void (*delete_node_t)(BitreeNode* node, BinaryTree* that);

class BitreeNode {
public:
    BitreeNode* left = nullptr;
    BitreeNode* right = nullptr;
    void* data;
    BitreeNode(void* data_ = nullptr)
        : data{ data_ } {};
    BitreeNode(const BitreeNode& node)
        : left{ node.left }
        , right{ node.right }
        , data{ node.data } {};
};

class BinaryTree {
protected:
    unsigned int size = 0;
    BitreeNode* root = nullptr;

public:
    destroy_t destroy_ = nullptr;

    BinaryTree(destroy_t destroy = nullptr)
        : destroy_{ destroy } {};
    BinaryTree(BinaryTree& bitree);
    ~BinaryTree();
    void destroy(void);
    void destroy(destroy_t destroy);
    bool insertLeft(BitreeNode* node, void* data);
    bool insertRight(BitreeNode* node, void* data);
    bool removeLeft(BitreeNode* node);
    bool removeRight(BitreeNode* node);
    bool merge(BinaryTree* root, BinaryTree* left, BinaryTree* right);
    unsigned int getSize(void) { return size; };
    BitreeNode* getRoot(void) { return root; };
    bool contain(BitreeNode* node);
    bool isEndOfBranch(BitreeNode* node);
    bool isLeaf(BitreeNode* node) { return node && !node->left && !node->right; };
    void* getData(BitreeNode* node) { return node ? node->data : nullptr; };
    BitreeNode* getLeft(BitreeNode* node) { return node ? node->left : nullptr; };
    BitreeNode* getRight(BitreeNode* node) { return node ? node->right : nullptr; };
    void scanPreorder(callback_t callback, BitreeNode* rootNode = nullptr);
    void scanPreorder(delete_node_t deleteFunc, BitreeNode* rootNode = nullptr, BinaryTree* that = nullptr);
    void scanInorder(callback_t callback, BitreeNode* rootNode = nullptr);
    void scanInorder(delete_node_t deleteFunc, BitreeNode* rootNode = nullptr, BinaryTree* that = nullptr);
    void scanPostorder(callback_t callback, BitreeNode* rootNode = nullptr);
    void scanPostorder(delete_node_t deleteFunc, BitreeNode* rootNode = nullptr, BinaryTree* that = nullptr);
};

#endif // BINARY_TREE_HPP