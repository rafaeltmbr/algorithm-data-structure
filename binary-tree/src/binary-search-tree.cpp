#include "../include/binary-search-tree.hpp"

bool BinarySearchTree::insert(void *data)
{
    if (!root) {
        root = new BitreeSNode(data);
        size++;
        return true;
    }

    BitreeSNode **n = (BitreeSNode**) &root;
    while(n && *n && (*n)->visible) {
        int i = compare((*n)->data, data);
        if (i == 0)
            return false;
        else if (i < 0)
            n = (BitreeSNode**) &(*n)->left;
        else
            n = (BitreeSNode**) &(*n)->right;
    }

    *n = new BitreeSNode(data);
    size++;
    return true;
}

bool BinarySearchTree::remove(void *data)
{
    if (!root)
        return false;

    BitreeSNode *n = (BitreeSNode*) root;
    while(n && n->visible) {
        int i = compare(n->data, data);
        if (i == 0) {
            n->visible = false;
            return true;
        } else if (i < 0)
            n = (BitreeSNode*) n->left;
        else
            n = (BitreeSNode*) n->right;
    }
    
    return false;
}

void* BinarySearchTree::lookup(void *data)
{
    if (!root)
        return nullptr;

    BitreeSNode *n = (BitreeSNode*) root;
    while(n && n->visible) {
        int i = compare(n->data, data);
        if (i == 0)
            return n->data;
        else if (i < 0)
            n = (BitreeSNode*) n->left;
        else
            n = (BitreeSNode*) n->right;
    }
    
    return nullptr;
}
