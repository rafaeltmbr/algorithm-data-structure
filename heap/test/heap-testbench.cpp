/* Build with:
    g++ heap-testbench.cpp ../src/heap.cpp -g -Wall -std=c++14 -o heap.exe
*/

#define ASSERT(cond, msg)                                                      \
    if (cond)                                                                  \
        std::cout << "#";                                                      \
    else {                                                                     \
        std::cerr << "Test failed (" << __LINE__ << "): " << msg << std::endl; \
        exit(EXIT_FAILURE);                                                    \
    }

#include "../include/heap.hpp"
#include <iostream>

using namespace std;

void testConstructor(Heap& heap);
void testInsert(Heap& heap);
void testExtract(Heap& heap);
void testDestroy(Heap& heap);
int compareInt(const void* data1, const void* data2);

#define ARRAY_SIZE 15
int intArray[ARRAY_SIZE] = {
    0, 10, 20, 30, 40, 50, 60, 70, -10, -20, -30, -40, -50, -60, -70
};

int main()
{
    cout << "------------------------ Heap Testbench ------------------------\n";
    Heap heap;
    testConstructor(heap);
    testInsert(heap);
    testExtract(heap);
    testDestroy(heap);
    cout << "------------------------ Testbench SUCCEED ------------------------" << endl;
}

void testConstructor(Heap& heap)
{
    cout << " Constructor test: ";
    ASSERT(heap.getSize() == 0, "getSize() failed");

    heap.setCompare(compareInt);
    for (int i = 0; i < ARRAY_SIZE; i++)
        ASSERT(heap.insert(intArray + i), "insert() failed on itertion " << i);
    ASSERT(heap.getSize() == ARRAY_SIZE, "getSize() failed");

    Heap copy(heap);
    ASSERT(copy.getSize() == ARRAY_SIZE, "getSize() failed");
    heap.destroy();
    ASSERT(heap.getSize() == 0, "getSize() failed");
    ASSERT(copy.getSize() == ARRAY_SIZE, "getSize() failed");

    ASSERT(*(int*)heap[0] == 70, "heap greater element failed");

    cout << " PASSED\n";
}

void testInsert(Heap& heap)
{
    cout << " Insert test: ";

    ASSERT(heap.getSize() == 0, "getSize() failed");
    ASSERT(!heap.insert(intArray), "insert() failed");
    heap.setCompare(compareInt);

    ASSERT(!heap.setAllocationBlockSize(0), "setAllocationBlockSize() failed");
    ASSERT(heap.setAllocationBlockSize(20), "setAllocationBlockSize() failed");

    for (int i = 0; i < ARRAY_SIZE; i++)
        ASSERT(heap.insert(intArray + i), "insert() failed on iteration " << i);
    ASSERT(heap.getSize() == ARRAY_SIZE, "getSize() failed");
    ASSERT(heap.getAllocatedSize() == 20, "getAllocatedSize() failed");

    ASSERT(*(int*)heap[0] == 70, "heap greater element failed");

    for (int i = 0; i < ARRAY_SIZE - 1; i++)
        ASSERT(!heap.insert(intArray + i), "insert() failed on iteration " << i);
    ASSERT(heap.getSize() == ARRAY_SIZE, "getSize() failed");
    ASSERT(heap.getAllocatedSize() == 20, "getAllocatedSize() failed");

    ASSERT(!heap.insert(nullptr), "insert() failed");

    ASSERT(heap.getSize() == ARRAY_SIZE, "getSize() failed");
    cout << " PASSED\n";
}

void testExtract(Heap& heap)
{
    cout << " Extract test: ";

    ASSERT(heap.getSize() == ARRAY_SIZE, "getSize() failed");

    ASSERT(*(int*)heap.extract(heap[0]) == 70, "extract() failed");

    for (int i = 0; i < ARRAY_SIZE - 1; i++)
        ASSERT(heap.extract(intArray + i), "insert() failed on iteration " << i);
    ASSERT(heap.getSize() == ARRAY_SIZE, "getSize() failed");

    heap.destroy();
    ASSERT(!heap.extract(intArray), "extract() failed");
    ASSERT(!heap.insert(intArray), "insert() failed");
    ASSERT(heap.getSize() == 0, "getSize() failed");
    ASSERT(heap.getAllocatedSize() == 0, "getAllocatedSize() failed");

    cout << " PASSED\n";
}

void testDestroy(Heap& heap)
{
    cout << " Destroy test: ";
    ASSERT(heap.getSize() == 0, "getSize() failed");
    ASSERT(heap.getAllocatedSize() == 0, "getAllocatedSize() failed");

    heap.setCompare([](const void* data1, const void* data2) {
        string s1 = *(string*)data1;
        string s2 = *(string*)data2;
        return s1 == s2 ? 0 : s1 > s2 ? 1 : -1;
    });

    const unsigned int arraySize = 3;
    string stringArray[arraySize] = { "Congratulations", "Destruction", "Succeed" };
    static string answer;

    for (unsigned int i = 0; i < arraySize; i++)
        ASSERT(heap.insert(stringArray + i), "insert() failed");
    ASSERT(heap.getSize() == arraySize, "getSize() failed");

    heap.setDestroy([](void* data) {
        answer += *(string*)data + " ";
    });
    ASSERT(answer == "Congratulations Destruction Succeed", "destroy() failed");

    ASSERT(heap.getSize() == 0, "getSize() failed");
    ASSERT(heap.getAllocatedSize() == 0, "getAllocatedSize() failed");
    cout << " PASSED\n";
}

int compareInt(const void* data1, const void* data2)
{
    return *(int*)data1 - *(int*)data2;
}