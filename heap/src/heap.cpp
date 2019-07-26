#include "../include/heap.hpp"

Heap::Heap(Heap& heap)
{
    size = heap.size;
    blockSize = heap.blockSize;
    allocatedSize = heap.allocatedSize;
    compare = heap.compare;
    destroy_ = heap.destroy_;
    tree = new void*[allocatedSize];

    for (unsigned int i = 0; i < size - 1; i++)
        tree[i] = heap.tree[i];
}

void Heap::destroy(void)
{
    if (destroy_) {
        while (size > 0) {
            size--;
            destroy_(tree[size]);
        }
    }

    delete[] tree;
    tree = nullptr;
    size = 0;
    allocatedSize = 0;
    destroy_ = nullptr;
    compare = nullptr;
}

static void swap(void** data1, void** data2)
{
    void* temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

bool Heap::insert(void* data)
{
    if (!data || !compare)
        return false;

    int index = getIndex(data);
    if (index >= 0) {
        tree[index] = data;
        return false;
    }

    if (size + 1 > allocatedSize)
        reallocatedTree(allocatedSize + blockSize);

    tree[size++] = data;
    adjustGreaterPosition(size - 1);
    return true;
}

void* Heap::extract(void* data)
{
    if (!size || !data || !compare)
        return nullptr;

    int index = getIndex(data);
    if (index < 0)
        return nullptr;

    void* temp = tree[index];

    unsigned int i, nextIndex;
    for (i = index; i < size - 1; i = nextIndex) {
        nextIndex = getGreaterChild(i);
        if ((signed)nextIndex < 0)
            break;
        swap(tree + i, tree + nextIndex);
    }

    size--;
    if (size)
        tree[i] = tree[size - 1];
    adjustGreaterPosition(i);
    return temp;
}

bool Heap::setAllocationBlockSize(unsigned int blockSize)
{
    if (!blockSize)
        return false;

    this->blockSize = blockSize;
    return true;
}

int Heap::getIndex(void* data)
{
    if (!data || !compare)
        return -1;

    for (unsigned int i = 0; i < size; i++)
        if (compare(data, tree[i]) == 0)
            return i;

    return -1;
}

int Heap::getGreaterChild(unsigned int index)
{
    if (index < 0 || index >= size)
        return -1;

    int right = getRightIndex(index) < (signed)size ? getRightIndex(index) : -1;
    int left = getLeftIndex(index) < (signed)size ? getLeftIndex(index) : -1;

    if (right == -1)
        return left;

    if (left == -1)
        return right;

    int cmp = compare(tree[left], tree[right]);
    return cmp > 0 ? left : right;
}

void Heap::adjustGreaterPosition(unsigned int index)
{
    if (index >= size)
        return;

    for (int i = index, parentIndex; i > 0; i = parentIndex) {
        parentIndex = getParentIndex(i);
        if (compare(tree[i], tree[parentIndex]) > 0)
            swap(tree + i, tree + parentIndex);
        else
            break;
        
    }
}

void Heap::reallocatedTree(unsigned int nodes)
{
    allocatedSize = nodes;
    void** newTree = new void*[nodes];
    unsigned int upBound = nodes < size ? nodes : size;
    for (unsigned int i = 0; i < upBound; i++)
        newTree[i] = tree[i];
    delete[] tree;
    tree = newTree;
}
