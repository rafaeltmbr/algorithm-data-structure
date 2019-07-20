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
    if (!entry)
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

    BitreeSNode* element = *entry;

    if (compare(data, element->data) == 0)
        return entry;

    if (element->left)
        if (getNode(data, &element->left))
            return &element->left;

    if (element->right)
        if (getNode(data, &element->right))
            return &element->right;

    return nullptr;
}

BitreeSNode* BinarySearchTree::getNode(void* data)
{
    BitreeSNode** node = getNode(data, &root);
    return node ? *node : nullptr;
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
    while (n && *n) {
        int i = compare(data, (*n)->data);
        if (i == 0) {
            if ((*n)->visible)
                return false;
            (*n)->visible = true;
            return true;
        } else if (i < 0) {
            n = &(*n)->left;
        } else {
            n = &(*n)->right;
        }
    }

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
