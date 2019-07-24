#include "../include/binary-search-tree.hpp"

BinarySearchTree::BinarySearchTree(BinarySearchTree& bstree)
{
    compare = bstree.compare;
    destroy_ = bstree.destroy_;
    insertBranch(bstree.root);
}

void BinarySearchTree::deleteNodes(BitreeSNode** node)
{
    if (!node || !*node)
        return;

    BitreeSNode* element = *node;

    if (element->left)
        deleteNodes(&element->left);

    if (element->right)
        deleteNodes(&element->right);

    if (destroy_)
        destroy_(element->data);
    delete element;

    *node = nullptr;
    size--;
}

bool BinarySearchTree::deleteBranch(void* data)
{
    if (!root || !data || !compare)
        return false;

    BitreeSNode** entry = getNode(data, &root);
    if (!entry || !*entry || !(*entry)->data)
        return false;

    deleteNodes(entry);
    return true;
}

bool BinarySearchTree::insertBranch(BitreeSNode* node)
{
    if (!node)
        return false;

    insert(node->data);
    insertBranch(node->left);
    insertBranch(node->right);
    return true;
}

BitreeSNode** BinarySearchTree::getNode(void* data, BitreeSNode** entry)
{
    if (!root || !data || !compare)
        return nullptr;

    if (!entry || !*entry)
        return entry;

    BitreeSNode* element = *entry;

    int cmp = compare(data, element->data);
    if (cmp == 0)
        return entry;
    else if (cmp < 0)
        return getNode(data, &element->left);
    else
        return getNode(data, &element->right);
}

BitreeSNode* BinarySearchTree::getNode(void* data)
{
    BitreeSNode** node = getNode(data, &root);
    return (node && *node && (*node)->data) ? *node : nullptr;
}

int BinarySearchTree::updateNodeHeight(void* data, BitreeSNode* node)
{
    if (!node || !data || !compare)
        return 0;

    int cmp = compare(data, node->data);
    if (cmp == 0)
        return node->height;

    int leftHeight, rightHeight;

    if (cmp > 0) {
        leftHeight = node->left ? node->left->height : 0;
        rightHeight = updateNodeHeight(data, node->right);
    } else {
        rightHeight = node->right ? node->right->height : 0;
        leftHeight = updateNodeHeight(data, node->left);
    }

    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    return node->height;
}

int BinarySearchTree::updateEveryNodeHeight(BitreeSNode* node)
{
    if (!node || !compare)
        return 0;

    int leftHeight = updateEveryNodeHeight(node->left);
    int rightHeight = updateEveryNodeHeight(node->right);

    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    return node->height;
}

BitreeSNode* BinarySearchTree::getUnbalacedNode(void* data, BitreeSNode* node)
{
    if (!node || !data || node->data == data)
        return nullptr;

    BitreeSNode* next;
    int cmp = compare(data, node->data);

    if (cmp < 0 && (next = getUnbalacedNode(data, node->left)))
        return next;

    if (cmp > 0 && (next = getUnbalacedNode(data, node->right)))
        return next;

    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    int diff = leftHeight - rightHeight;
    if (diff < -1 || diff > 1)
        return node;

    return nullptr;
}

void BinarySearchTree::balanceSubtree(void* data, BitreeSNode* node)
{
    if (!data || !node)
        return;

    BitreeSNode** prev = getNode(node->data, &root);
    if (!prev)
        prev = &root;

    int leftCompare = node->left ? compare(data, node->left->data) : 0;
    int rightCompare = node->right ? compare(data, node->right->data) : 0;

    if (leftCompare < 0)
        rotateRight(node, prev);
    else if (leftCompare > 0) {
        rotateLeft(node->left, &node->left);
        rotateRight(node, prev);
    } else if (rightCompare < 0) {
        rotateRight(node->right, &node->right);
        rotateLeft(node, prev);
    } else if (rightCompare > 0)
        rotateLeft(node, prev);
}

void BinarySearchTree::keepAVLTree(void* data)
{
    updateNodeHeight(data, root);
    BitreeSNode* unbalanced = getUnbalacedNode(data, root);
    if (unbalanced)
        balanceSubtree(data, unbalanced);
    updateEveryNodeHeight(root);
}
bool BinarySearchTree::insert(void* data)
{
    if (!data)
        return false;

    BitreeSNode** n = root ? getNode(data, &root) : &root;

    if (!n || (*n && (*n)->visible))
        return false;

    *n = new BitreeSNode(data);
    size++;
    keepAVLTree(data);

    return true;
}

bool BinarySearchTree::remove(void* data)
{
    BitreeSNode* n = getNode(data);
    if (!n)
        return false;

    n->visible = false;
    return true;
}

void* BinarySearchTree::lookup(void* data)
{
    BitreeSNode* n = getNode(data);
    return (!n || !n->visible) ? nullptr : n->data;
}

void BinarySearchTree::destroy(void)
{
    deleteNodes(&root);
    compare = nullptr;
    destroy_ = nullptr;
}

void BinarySearchTree::rotateRight(BitreeSNode* node, BitreeSNode** prev)
{
    if (!node || !node->left)
        return;

    BitreeSNode* leftTree = node->left;
    node->left = leftTree->right;
    leftTree->right = node;

    if (prev)
        *prev = leftTree;
}

void BinarySearchTree::rotateLeft(BitreeSNode* node, BitreeSNode** prev)
{
    if (!node || !node->right)
        return;

    BitreeSNode* rightTree = node->right;
    node->right = rightTree->left;
    rightTree->left = node;

    if (prev)
        *prev = rightTree;
}
