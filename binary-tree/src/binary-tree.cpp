#include "../include/binary-tree.hpp"

static void newNodeCopy(BitreeNode* node)
{
    /* wrong! coping old node right and left references */
    BitreeNode* copyNode = new BitreeNode(node->data);
    copyNode->left = node->left;
    copyNode->right = node->right;
}

BinaryTree::BinaryTree(BinaryTree& bitree)
{
    scanPreorder(newNodeCopy);
    destroy_ = bitree.destroy_;
    root = bitree.root;
    size = bitree.size;
}

BinaryTree::~BinaryTree(void)
{
    destroy(nullptr);
    root = nullptr;
    destroy_ = nullptr;
}

void destroyDataDeleteNode(BitreeNode* node, BinaryTree* that)
{
    if (that)
        that->destroy_(node->data);
    delete node;
}

void BinaryTree::destroy(void)
{
    scanPostorder(destroyDataDeleteNode);
    destroy_ = nullptr;
    root = nullptr;
    size = 0;
}

void BinaryTree::destroy(destroy_t destroy)
{
    destroy_ = destroy;
    this->destroy();
}

bool BinaryTree::insertLeft(BitreeNode* node, void* data)
{
    if ((!node && !root) || (node && !node->left)) {
        if (!node)
            root = node->left;
        else
            node->left = new BitreeNode(data);
        return true;
    }

    return false;
}

bool BinaryTree::insertRight(BitreeNode* node, void* data)
{
    if ((!node && !root) || (node && !node->right)) {
        if (!node)
            root = node->right;
        else
            node->right = new BitreeNode(data);
        return true;
    }

    return false;
}

bool BinaryTree::removeLeft(BitreeNode* node)
{
    if (node)
        scanPostorder(destroyDataDeleteNode, node->left);
    else
        scanPostorder(destroyDataDeleteNode);
    return false;
}

bool BinaryTree::removeRight(BitreeNode* node)
{
    if (node)
        scanPostorder(destroyDataDeleteNode, node->right);
    else
        scanPostorder(destroyDataDeleteNode);
    return false;
}

bool BinaryTree::merge(BinaryTree* root, BinaryTree* left, BinaryTree* right)
{
    return false;
}

bool BinaryTree::contain(BitreeNode* node)
{
    return false;
}

bool BinaryTree::isEndOfBranch(BitreeNode* node)
{
    return false;
}

void BinaryTree::scanPreorder(callback_t callback, BitreeNode* rootNode)
{
}

void BinaryTree::scanPreorder(delete_node_t deleteFunc, BitreeNode* rootNode, BinaryTree* that)
{
}

void BinaryTree::scanInorder(callback_t callback, BitreeNode* rootNode)
{
}

void BinaryTree::scanInorder(delete_node_t deleteFunc, BitreeNode* rootNode, BinaryTree* that)
{
}

void BinaryTree::scanPostorder(callback_t callback, BitreeNode* rootNode)
{
}

void BinaryTree::scanPostorder(delete_node_t deleteFunc, BitreeNode* rootNode, BinaryTree* that)
{
}