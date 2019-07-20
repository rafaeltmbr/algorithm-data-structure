#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

typedef int (*compare_t)(const void* data1, const void* data2);
typedef void (*destroy_t)(void* data);

class BitreeSNode {
    BitreeSNode* left = nullptr;
    BitreeSNode* right = nullptr;
    bool visible = true;
    int balance = 0;
    friend class BinarySearchTree;

public:
    void* data = nullptr;
    BitreeSNode(void* data_)
        : data{ data_ } {};
};

class BinarySearchTree {
protected:
    int size = 0;
    BitreeSNode* root = nullptr;
    compare_t compare = nullptr;
    destroy_t destroy_ = nullptr;
    void deleteNodes(BitreeSNode** node);
    BitreeSNode** getNode(void* data, BitreeSNode** entry);

public:
    BinarySearchTree(compare_t compareFunc = nullptr, destroy_t destroyFunc = nullptr)
        : compare{ compareFunc }
        , destroy_{ destroyFunc } {};
    BinarySearchTree(BinarySearchTree& bstree);
    ~BinarySearchTree() { destroy(); }
    void destroy(void);
    void setDestroy(destroy_t destroy) { destroy_ = destroy; }
    void setCompare(compare_t compare) { this->compare = compare; }
    bool deleteBranch(void* data);
    bool insertBranch(BitreeSNode* node);
    bool insert(void* data);
    bool remove(void* data);
    void* lookup(void* data);
    int getSize(void) { return size; }
    BitreeSNode* getRoot(void) { return root; }
    BitreeSNode* getNode(void* data);
    static void* getData(BitreeSNode* node) { return node ? node->data : nullptr; }
};

#endif // BINARY_SEARCH_TREE_HPP