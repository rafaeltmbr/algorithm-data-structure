#include "../include/binary-tree.hpp"

bool isNodeEqual(BitreeNode* node1, BitreeNode* node2)
{
    return node1 && node2
        && node1->data == node2->data
        && node1->right == node2->right
        && node1->left == node2->left;
}

BitreeNode* BinaryTree::copyNodesRecursively(BitreeNode *node)
{
    if (!node)
        return nullptr;

    BitreeNode *n = new BitreeNode(node->data);

    n->left = copyNodesRecursively(node->left);
    n->right = copyNodesRecursively(node->right);
    size++;

    return n;
}

BinaryTree::BinaryTree(BinaryTree& bitree)
{
    root = copyNodesRecursively(bitree.root);
    destroy_ = bitree.destroy_;
    size = bitree.size;
}

BinaryTree::~BinaryTree(void)
{
    destroy(nullptr);
    root = nullptr;
    destroy_ = nullptr;
}

void BinaryTree::destroyDataDeleteNode(BitreeNode** node)
{
    if (!node)
        return;

    BitreeNode *element = *node;
    if (!element)
        return;

    if (element->left)
        destroyDataDeleteNode(&element->left);

    if (element->right)
        destroyDataDeleteNode(&element->right);

    if (destroy_)
        destroy_(element->data);
    delete element;

    *node = nullptr;
    size--;
}

void BinaryTree::destroy(void)
{
    destroyDataDeleteNode(&root);
    destroy_ = nullptr;
    root = nullptr;
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
            root = new BitreeNode(data);
        else
            node->left = new BitreeNode(data);
        size++;
        return true;
    }

    return false;
}

bool BinaryTree::insertRight(BitreeNode* node, void* data)
{
    if ((!node && !root) || (node && !node->right)) {
        if (!node)
            root = new BitreeNode(data);
        else
            node->right = new BitreeNode(data);
        size++;
        return true;
    }

    return false;
}

bool BinaryTree::removeLeft(BitreeNode* node)
{
    if (node) {
        if (!node->left)
            return false;
        destroyDataDeleteNode(&node->left);
    } else {
        destroyDataDeleteNode(&root);
    }

    return size >= 0;
}

bool BinaryTree::removeRight(BitreeNode* node)
{
    if (node) {
        if (!node->right)
            return false;
        destroyDataDeleteNode(&node->right);
    } else {
        destroyDataDeleteNode(&root);
    }
    
    return size >= 0;
}

bool BinaryTree::merge(BinaryTree& left, BinaryTree& right)
{
    if (root)
        return false;

    root = new BitreeNode;
    root->left = copyNodesRecursively(left.root);
    root->right = copyNodesRecursively(right.root);
    size++;

    return size == left.size + right.size + 1;
}

bool BinaryTree::isEndOfBranch(BitreeNode* node)
{
    return false;
}

void BinaryTree::scanPreorder(callback_t callback, BitreeNode* node)
{
    if (!callback || !root)
        return;

    if (!node)
        node = root;

    callback(node);

    if (node->left)
        scanPreorder(callback, node->left);

    if (node->right)
        scanPreorder(callback, node->right);
}

void BinaryTree::scanInorder(callback_t callback, BitreeNode* node)
{
    if (!callback || !root)
        return;

    if (!node)
        node = root;

    if (node->left)
        scanInorder(callback, node->left);

    callback(node);

    if (node->right)
        scanInorder(callback, node->right);
}

void BinaryTree::scanPostorder(callback_t callback, BitreeNode* node)
{
    if (!callback || !root)
        return;

    if (!node)
        node = root;

    if (node->left)
        scanPostorder(callback, node->left);

    if (node->right)
        scanPostorder(callback, node->right);

    callback(node);
}
