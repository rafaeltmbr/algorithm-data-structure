/*
    g++ chained-hash-table-testbench.cpp ../../set/src/set.cpp ../../list/src/list.cpp ../src/chained-hash-table.cpp -g -Wall -std=c++14 -o chtable.exe
*/

#include "../include/chained-hash-table.hpp"
#include <iostream>
#include <cstdint>

using namespace std;

#define ASSERT(cond, msg) { \
    if ( !(cond) ) { \
        std::cout << "Test failed (" << __LINE__ << "): " << msg << std::endl; \
        exit(EXIT_FAILURE); \
    } \
}
#define DA_SIZE 11

class Define {
public:
    Define(const char *name, const char *value = "") {
        this->name = name;
        this->value = value;
    }
    string name;
    string value;
};

Define da[DA_SIZE] = {
    {"big", "bigger"},
    {"small", "smaller"},
    {"dog", "big dog"},
    {"cat", "big cat"},
    {"fast", "faster"},
    {"slow", "slower"},
    {"short", "shorter"},
    {"week", "weeker"},
    {"strong", "stronger"},
    {"good", "best"},
    {"bad", "worst"}
};

Define de[DA_SIZE] = {
    {"big", ""},
    {"small", ""},
    {"dog", ""},
    {"cat", ""},
    {"fast", ""},
    {"slow", ""},
    {"short", ""},
    {"week", ""},
    {"strong", ""},
    {"good", ""},
    {"bad", ""}
};

void testContructor(ChainedHashTable &chtable);
void testInsertRemoveLookup(ChainedHashTable &chtable);
void testLookup(ChainedHashTable &chtable);
void testDestroy(ChainedHashTable &chtable);
bool matchName(const void *data1, const void *data2);
int hashFunc(const void*data, int keys);
int generatePJWKey(string &data);
int hashDiv(int key, int keys);
int hashMult(int key, int keys);

int main()
{
    cout << "-------------------- Chained Hash Table Testbench -----------------\n";
    ChainedHashTable chtable(5, hashFunc, matchName);
    testContructor(chtable);
    testInsertRemoveLookup(chtable);
    testDestroy(chtable);
    cout << "-------------------------- Test SUCCEED --------------------------" << endl;
}

void testContructor(ChainedHashTable &chtable)
{
    ASSERT(chtable.getSize() == 0, "table must be empty");
    ASSERT(chtable.insert(da+2) == true, "insert() failed");
    ASSERT(chtable.insert(da+3) == true, "insert() failed");
    ASSERT(chtable.insert(da+5) == true, "insert() failed");
    ASSERT(chtable.insert(da+7) == true, "insert() failed");
    ASSERT(chtable.getSize() == 4, "getSize() failed");

    ChainedHashTable copy(chtable);
    ASSERT(copy.getSize() == 4, "size mismatch");
    ASSERT( matchName(chtable.remove(de+2), copy.remove(da+2) ), "remove() failed");
    ASSERT(!matchName(chtable.remove(de+3), copy.remove(da+5) ), "remove() failed");
    ASSERT(!matchName(chtable.remove(de+5), copy.remove(da+3) ), "remove() failed");
    ASSERT( matchName(chtable.remove(de+7), copy.remove(da+7) ), "remove() failed");

    ASSERT(chtable.getSize() == 0, "table must be empty");
    ASSERT(copy.getSize() == 0, "table must be empty");
    cout << " Constructor Test PASSED" << endl;
}

void testInsertRemoveLookup(ChainedHashTable &chtable)
{
    ASSERT(chtable.getSize() == 0, "table must be empty");

    for (int i=0; i < DA_SIZE; i++)
        ASSERT(chtable.insert(da+i), "interation(" << i << ") failed");
    ASSERT(chtable.getSize() == DA_SIZE, "getSize() failed");

    ASSERT(chtable.remove(da+DA_SIZE-1), "remove() failed");
    ASSERT(!chtable.lookup(da+DA_SIZE-1), "lookup() failed");
    ASSERT(chtable.getSize() == DA_SIZE-1, "getSize() failed");

    for (int i=0; i < chtable.getSize(); i++)
        ASSERT(chtable.lookup(de+i), "lookup() failed");

    ASSERT(chtable.getSize() == DA_SIZE-1, "getSize() failed");
    chtable.destroy();
    ASSERT(chtable.getSize() == 0, "table must be empty");

    cout << " Insert, Remove and Lookup Test PASSED" << endl;
}

void destroy(void *data)
{
    int *i = (int*) data;
    (*i)++;
}

bool matchInt(const void *data1, const void* data2)
{
    return *(int*) data1 == *(int*) data2;
}

void testDestroy(ChainedHashTable &chtable)
{
    int d = 10;
    chtable.setDestroy(destroy);
    chtable.setMatch(matchInt);

    ASSERT(chtable.getSize() == 0, "table must be empty");
    ASSERT(chtable.insert(&d), "insert() failed");
    ASSERT(!chtable.insert(&d), "insert() failed");
    ASSERT(chtable.getSize() == 1, "getSize() failed");

    chtable.destroy();
    ASSERT(d == 11, "destroy() failed");
    ASSERT(chtable.getSize() == 0, "table must be empty");

    cout << " Destroy Test PASSED" << endl;
}

bool matchName(const void *data1, const void *data2)
{
    if (data1 == nullptr || data2 == nullptr)
        return false;

    const Define &dt1 = *(Define*) data1;
    const Define &dt2 = *(Define*) data2;
    return dt1.name == dt2.name;
}

int hashFunc(const void*data, int keys)
{
    if (!data)
        return -1;

    return hashDiv( generatePJWKey(*(string*) data), keys );
}

int generatePJWKey(string &data)
{
    int acc = 0;
    int size = data.size();

    for (int i=0, temp; i < size; i++) {
        acc = (acc << 4) + data[i];
        if ( (temp = (acc & 0xf0000000)) ) {
            acc = acc ^ (temp >> 24);
            acc = acc ^ temp;
        }
    }

    return acc;
}

int hashDiv(int key, int keys)
{
    return key % keys;
}

int hashMult(int key, int keys)
{
    const double A = 0.61803398874989484820458683436564; // ( sqrt(5) - 1 ) / 2
    int integer = A * key;
    double fraction = A * key - integer;
    return fraction * keys;
}
