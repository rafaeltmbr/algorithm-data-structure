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

static BitreeNode* containNode;

bool BinaryTree::contain(BitreeNode* node)
{
    if (!node)
        return false;

    containNode = node;

    scanPreorder([](BitreeNode* n) {
        if (isNodeEqual(n, containNode))
            containNode = nullptr;
    });

    return containNode == nullptr;
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

void BinaryTree::scanPreorder(delete_node_t deleteFunc, BinaryTree* that, BitreeNode* node)
{
    if (!deleteFunc || !root)
        return;

    if (!node)
        node = root;

    deleteFunc(node, that);

    if (node->left)
        scanPreorder(deleteFunc, that, node->left);

    if (node->right)
        scanPreorder(deleteFunc, that, node->right);
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

void BinaryTree::scanInorder(delete_node_t deleteFunc, BinaryTree* that, BitreeNode* node)
{
    if (!deleteFunc || !root)
        return;

    if (!node)
        node = root;

    if (node->left)
        scanInorder(deleteFunc, that, node->left);

    deleteFunc(node, that);

    if (node->right)
        scanInorder(deleteFunc, that, node->right);
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

void BinaryTree::scanPostorder(delete_node_t deleteFunc, BinaryTree* that, BitreeNode* node)
{
    if (!deleteFunc || !root)
        return;

    if (!node)
        node = root;

    if (node->left)
        scanPostorder(deleteFunc, that, node->left);

    if (node->right)
        scanPostorder(deleteFunc, that, node->right);

    deleteFunc(node, that);
}