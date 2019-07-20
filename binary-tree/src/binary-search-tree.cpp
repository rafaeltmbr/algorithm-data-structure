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

    if (cmp > 1) {
        leftHeight = node->left ? node->left->height : 0;
        rightHeight = updateNodeHeight(data, node->right);
    } else {
        rightHeight = node->right ? node->right->height : 0;
        leftHeight = updateNodeHeight(data, node->left);
    }

    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    return node->height;
}

BitreeSNode* BinarySearchTree::getUnbalacedNode(BitreeSNode* node)
{
    if (!node)
        return nullptr;
    // all wrong !
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    int diff = leftHeight - rightHeight;
    if (diff < -1 || diff > 1)
        return node;

    if ((node = getUnbalacedNode(node->left)))
        return node;

    if ((node = getUnbalacedNode(node->right)))
        return node;

    return nullptr;
}

void BinarySearchTree::balanceSubtree(BitreeSNode* node)
{
    if (!node)
        return;

    int diffL = 0, diffR = 0;
    if (node->left) {
        int subLL = node->left->left ? node->left->left->height : 0;
        int subLR = node->left->right ? node->left->right->height : 0;
        diffL = subLL - subLR;
    }

    if (node->right) {
        int subRL = node->right->left ? node->right->left->height : 0;
        int subRR = node->right->right ? node->right->right->height : 0;
        diffR = subRL - subRR;
    }

    if (diffL < -1)
        rotateLL(node);
    if (diffL > 1)
        rotateLR(node);
    if (diffR < -1)
        rotateRL(node);
    if (diffR > 1)
        rotateRR(node);
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
    updateNodeHeight(data, root);
    balanceSubtree(getUnbalacedNode(root));
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

void BinarySearchTree::rotateLL(BitreeSNode* node)
{
}

void BinarySearchTree::rotateLR(BitreeSNode* node)
{
}

void BinarySearchTree::rotateRL(BitreeSNode* node)
{
}

void BinarySearchTree::rotateRR(BitreeSNode* node)
{
}