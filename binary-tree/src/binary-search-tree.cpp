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

bool BinarySearchTree::insert(void* data)
{
    if (!data)
        return false;

    BitreeSNode** n;

    if (root)
        n = getNode(data, &root);
    else
        n = &root;

    if (!n || (*n && (*n)->visible))
        return false;

    *n = new BitreeSNode(data);
    size++;
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
}
