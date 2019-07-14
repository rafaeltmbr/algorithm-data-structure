/*
    g++ open-addressed-hash-table-testbench.cpp ../src/open-addressed-hash-table.cpp -g -Wall -std=c++14 -o ohtable.exe
*/

#include "../include/open-addressed-hash-table.hpp"
#include <iostream>

using namespace std;

#define ASSERT(cond, msg) { \
    if ( !(cond) ) { \
        std::cout << "Test failed (" << __LINE__ << "): " << msg << std::endl; \
        exit(EXIT_FAILURE); \
    } \
}
#define DA_SIZE 11
#define HASH_KEYS 17

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

void testContructor(OpenAddressedHashTable &ohtable);
void testInsertRemoveLookup(OpenAddressedHashTable &ohtable);
void testLookup(OpenAddressedHashTable &ohtable);
void testDestroy(OpenAddressedHashTable &ohtable);
bool matchName(const void *data1, const void *data2);
int hashFunc1(const void*data, int keys);
int hashFunc2(const void*data, int keys);
int generatePJWKey(string &data);
int hashDiv(int key, int keys);
int hashMult(int key, int keys);

int main()
{
    cout << "-------------------- Chained Hash Table Testbench -----------------\n";
    OpenAddressedHashTable ohtable(11, hashFunc1, hashFunc2, matchName);
    testContructor(ohtable);
    testInsertRemoveLookup(ohtable);
    testDestroy(ohtable);
    cout << "-------------------------- Test SUCCEED --------------------------" << endl;
}

void testContructor(OpenAddressedHashTable &ohtable)
{
    ASSERT(ohtable.getSize() == 0, "table must be empty");
    ASSERT(ohtable.insert(da+2) == true, "insert() failed");
    ASSERT(ohtable.insert(da+3) == true, "insert() failed");
    ASSERT(ohtable.insert(da+5) == true, "insert() failed");
    ASSERT(ohtable.insert(da+7) == true, "insert() failed");
    ASSERT(ohtable.getSize() == 4, "getSize() failed");

    OpenAddressedHashTable copy(ohtable);
    ASSERT(copy.getSize() == 4, "size mismatch");
    ASSERT( matchName(ohtable.remove(de+2), copy.remove(da+2) ), "remove() failed");
    ASSERT(!matchName(ohtable.remove(de+3), copy.remove(da+5) ), "remove() failed");
    ASSERT(!matchName(ohtable.remove(de+5), copy.remove(da+3) ), "remove() failed");
    ASSERT( matchName(ohtable.remove(de+7), copy.remove(da+7) ), "remove() failed");

    ASSERT(ohtable.getSize() == 0, "table must be empty");
    ASSERT(copy.getSize() == 0, "table must be empty");
    cout << " Constructor Test PASSED" << endl;
}

void testInsertRemoveLookup(OpenAddressedHashTable &ohtable)
{
    ASSERT(ohtable.getSize() == 0, "table must be empty");

    for (int i=0; i < DA_SIZE; i++)
        ASSERT(ohtable.insert(da+i), "interation(" << i << ") failed");
    ASSERT(ohtable.getSize() == DA_SIZE, "getSize() failed");

    ASSERT(ohtable.remove(da+DA_SIZE-1), "remove() failed");
    ASSERT(!ohtable.lookup(da+DA_SIZE-1), "lookup() failed");
    ASSERT(ohtable.getSize() == DA_SIZE-1, "getSize() failed");

    for (int i=0; i < ohtable.getSize(); i++)
        ASSERT(ohtable.lookup(de+i), "lookup() failed");

    ASSERT(ohtable.getSize() == DA_SIZE-1, "getSize() failed");
    ohtable.destroy();
    ASSERT(ohtable.getSize() == 0, "table must be empty");

    cout << " Insert, Remove and Lookup Test PASSED" << endl;
}

void destroy(void *data)
{
    int *i = (int*) data;
    (*i)++;
}

bool matchInt(const void *data1, const void* data2)
{
    return (data1 && data2) ? *(int*) data1 == *(int*) data2 : false;
}

void testDestroy(OpenAddressedHashTable &ohtable)
{
    int d = 10;
    ohtable.setDestroy(destroy);
    ohtable.setMatch(matchInt);

    ASSERT(ohtable.getSize() == 0, "table must be empty");
    ASSERT(ohtable.insert(&d), "insert() failed");
    ASSERT(!ohtable.insert(&d), "insert() failed");
    ASSERT(ohtable.getSize() == 1, "getSize() failed");

    ohtable.destroy();
    ASSERT(d == 11, "destroy() failed");
    ASSERT(ohtable.getSize() == 0, "table must be empty");

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

int hashFunc1(const void*data, int keys)
{
    if (!data)
        return -1;

    return hashDiv( generatePJWKey(*(string*) data), keys );
}

int hashFunc2(const void*data, int keys)
{
    if (!data)
        return -1;

    return 1 + hashDiv( generatePJWKey(*(string*) data), keys-2 );
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