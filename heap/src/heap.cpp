#include "../include/heap.hpp"
#

void Heap::destroy(void)
{
    if (destroy_) {
        while (size > 0) {
            size--;
            destroy_(tree[size]);
        }
    }

    delete[] tree;
    allocatedSize = 0;
    destroy_ = nullptr;
    compare = nullptr;
}

static void swap(void* data1, void* data2)
{
    void* temp = data1;
    data1 = data2;
    data2 = temp;
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

    size++;
    if (size > blockSize) {
        allocatedSize += blockSize;
        void** newTree = new void*[allocatedSize];
        for (unsigned int i = 0; i < size - 1; i++)
            newTree[i] = tree[i];
        delete[] tree;
        tree = newTree;
    }

    tree[size - 1] = data;
    adjustGreaterPosition(size - 1);
    return true;
}

void* Heap::extract(void* data)
{
    if (!data || !compare)
        return nullptr;

    int index = getIndex(data);
    if (index < 0)
        return nullptr;

    void* temp = tree[index];

    unsigned int i, nextIndex;
    for (i = index; i < size - 1; i = nextIndex) {
        nextIndex = getGreaterChild(i);
        if (nextIndex < 0)
            break;
        swap(tree[index], tree[nextIndex]);
    }

    size--;
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

    int right = getRightIndex(index);
    int left = getLeftIndex(index);

    if (right == -1)
        return left;

    int cmp = compare(tree[left], tree[right]);
    return cmp == 0 ? -1
                    : cmp > 0 ? left
                              : right;
}

void Heap::adjustGreaterPosition(unsigned int index)
{
    for (int i = index - 1, parentIndex; i > 0; i = parentIndex) {
        parentIndex = getParentIndex(i);
        if (compare(tree[index], tree[parentIndex]) > 0)
            swap(tree[i], tree[parentIndex]);
    }
}