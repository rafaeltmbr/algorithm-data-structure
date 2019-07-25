#ifndef HEAP_HPP
#define HEAP_HPP

typedef void (*destroy_t)(void* data);
typedef int (*compare_t)(const void* data1, const void* data2);

class Heap {
protected:
    unsigned int size = 0, blockSize = 10, allocatedSize = 0;
    void** tree = nullptr;
    compare_t compare = nullptr;
    destroy_t destroy_ = nullptr;
    int getGreaterChild(unsigned int index);
    void adjustGreaterPosition(unsigned int index);

public:
    Heap(compare_t cmp = nullptr, destroy_t destroy = nullptr)
        : compare{ cmp }
        , destroy_{ destroy } {};
    ~Heap() { destroy(); };
    void destroy(void);
    bool insert(void* data);
    void* extract(void* data);
    bool setAllocationBlockSize(unsigned int blockSize);
    int getIndex(void* data);
    int getLeftIndex(unsigned int index) { return index < size ? 2 * index + 1 : -1; }
    int getRightIndex(unsigned int index) { return index < size ? 2 * index + 2 : -1; }
    int getParentIndex(unsigned int index) { return index < size && index > 0 ? (index - 1) / 2 : -1; }
    unsigned int getSize(void) { return size; }
    unsigned int getAllocatedSize(void) { return allocatedSize; }
    void setCompare(compare_t cmp) { compare = cmp; }
    void setDestroy(destroy_t destroy) { destroy_ = destroy; }
    void* operator[](unsigned int index) { return index < size ? tree[index] : nullptr; }
};

#endif // HEAP_HPP#ifndef HE#ifndef HE