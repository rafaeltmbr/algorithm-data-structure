#include "../include/binary-search-tree.hpp"

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

    BitreeSNode** entry = getNode(data);
    if (!entry)
        return false;

    deleteNodes(entry);
    return true;
}

BitreeSNode** BinarySearchTree::getNode(void* data, BitreeSNode** entry)
{
    if (!root || !data || !compare)
        return nullptr;

    if (!entry || !*entry)
        entry = &root;

    if (compare(data, (*entry)->data) == 0)
        return entry;

    if (!(*entry)->right)
        if (!getNode(data, &(*entry)->right))
            return &(*entry)->right;

    if (!(*entry)->left)
        if (!getNode(data, &(*entry)->left))
            return &(*entry)->left;

    return nullptr;
}

bool BinarySearchTree::insert(void* data)
{
    if (!data)
        return false;

    if (!root) {
        root = new BitreeSNode(data);
        size++;
        return true;
    }

    BitreeSNode** n = &root;
    while (n && *n && (*n)->visible) {
        int i = compare((*n)->data, data);
        if (i == 0)
            return false;
        else if (i < 0)
            n = &(*n)->left;
        else
            n = &(*n)->right;
    }

    *n = new BitreeSNode(data);
    size++;
    return true;
}

bool BinarySearchTree::remove(void* data)
{
    if (!root || !data)
        return false;

    BitreeSNode* n = root;
    while (n && n->visible) {
        int i = compare(n->data, data);
        if (i == 0) {
            n->visible = false;
            return true;
        } else if (i < 0)
            n = n->left;
        else
            n = n->right;
    }

    return false;
}

void* BinarySearchTree::lookup(void* data)
{
    if (!root || !data)
        return nullptr;

    BitreeSNode* n = root;
    while (n && n->visible) {
        int i = compare(n->data, data);
        if (i == 0)
            return n->data;
        else if (i < 0)
            n = n->left;
        else
            n = n->right;
    }

    return nullptr;
}

void BinarySearchTree::destroy(void)
{
    deleteNodes(&root);
}
