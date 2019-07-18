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
    if (that && node)
        that->destroy_(node->data);
    delete node;
}

void BinaryTree::destroy(void)
{
    scanPostorder(destroyDataDeleteNode, this);
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
    if (node) {
        if (!node->left)
            return false;
        scanPostorder(destroyDataDeleteNode, this, node->left);
    } else {
        scanPostorder(destroyDataDeleteNode);
    }

    return true;
}

bool BinaryTree::removeRight(BitreeNode* node)
{
    if (node) {
        if (!node->right)
            return false;
        scanPostorder(destroyDataDeleteNode, this, node->right);
    } else {
        scanPostorder(destroyDataDeleteNode);
    }

    return true;
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

void BinaryTree::scanPreorder(callback_t callback, BitreeNode* node)
{
    if (!callback)
        return;
        
    if (node)
        callback(node);
    else if (root)
        callback(root);
    else
        return;

    if (node->left)
        scanPreorder(callback, node->left);

    if (node->right)
        scanPreorder(callback, node->right);
}

void BinaryTree::scanPreorder(delete_node_t deleteFunc, BinaryTree* that, BitreeNode* node)
{
    if (!deleteFunc)
        return;

    if (node)
        deleteFunc(node, that);
    else if (root)
        deleteFunc(root, that);
    else
        return;

    if (node->left)
        scanPreorder(deleteFunc, that, node->left);

    if (node->right)
        scanPreorder(deleteFunc, that, node->right);
}

void BinaryTree::scanInorder(callback_t callback, BitreeNode* node)
{    
    if (!callback)
        return;
        
    if (node->left)
        scanPreorder(callback, node->left);

    if (node)
        callback(node);
    else if (root)
        callback(root);
    else
        return;

    if (node->right)
        scanPreorder(callback, node->right);
}

void BinaryTree::scanInorder(delete_node_t deleteFunc, BinaryTree* that, BitreeNode* node)
{
    if (!deleteFunc)
        return;
 
    if (node->left)
        scanPreorder(deleteFunc, that, node->left);

    if (node)
        deleteFunc(node, that);
    else if (root)
        deleteFunc(root, that);
    else
        return;

    if (node->right)
        scanPreorder(deleteFunc, that, node->right);
}

void BinaryTree::scanPostorder(callback_t callback, BitreeNode* node)
{
    if (!callback)
        return;

    if (node->left)
        scanPreorder(callback, node->left);

    if (node->right)
        scanPreorder(callback, node->right);

    if (node)
        callback(node);
    else if (root)
        callback(root);
}

void BinaryTree::scanPostorder(delete_node_t deleteFunc, BinaryTree* that, BitreeNode* node)
{
    if (!deleteFunc)
        return;
 
    if (node->left)
        scanPreorder(deleteFunc, that, node->left);
    
    if (node->right)
        scanPreorder(deleteFunc, that, node->right);

    if (node)
        deleteFunc(node, that);
    else if (root)
        deleteFunc(root, that);
}