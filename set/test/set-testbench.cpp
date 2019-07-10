/**
 * Buil commands:
 *  g++ set-testbench.cpp ../src/set.cpp ../../list/src/list.cpp -g -Wall -std=c++14 -o set.exe
 */
#include "../include/set.hpp"
#include <iostream>

#define ASSERT(cond, msg) { \
    if ( !(cond) ) { \
        std::cout << "Test failed (" << __LINE__ << "): " << msg << std::endl; \
        exit(EXIT_FAILURE); \
    } \
}

using namespace std;

void testInsertRemove(Set &set);
void testUnion(Set &set);
void testIntersection(Set &set);
void testDifference(Set &set);
void testIsMethods(Set &set);
void testDestroy(Set &set);
bool matchInt(void *data1, void *data2);

int main()
{
    cout << "------------------------ Set Testbench ------------------------\n";
    Set set(matchInt, nullptr);
    testInsertRemove(set);
    testUnion(set);
    testIntersection(set);
    testDifference(set);
    testIsMethods(set);
    testDestroy(set);
    cout << "------------------------- Set SUCCEED -------------------------" << endl;
}

void testInsertRemove(Set &set)
{
    ASSERT(set.getSize() == 0, "getSize() failed");

    int i1 = 2018, i2 = 2022, i3 = 2026;
    int i4 = 2018, i5 = 2020;

    ASSERT(set.insert(&i1), "insert() failed");
    ASSERT(set.insert(&i2), "insert() failed");
    ASSERT(set.insert(&i3), "insert() failed");
    ASSERT(set.getSize() == 3, "getSize() failed");

    ASSERT(set.isMember(&i4), "isMember() failed");
    ASSERT(set.isMember(&i2), "isMember() failed");
    ASSERT(set.isMember(&i3), "isMember() failed");
    ASSERT(!set.isMember(&i5), "isMember() failed");

    ASSERT(set.remove(&i4), "remove() failed");
    ASSERT(set.remove(&i2), "remove() failed");
    ASSERT(set.remove(&i3), "remove() failed");
    ASSERT(!set.remove(&i5), "remove() failed");
    ASSERT(set.getSize() == 0, "getSize() failed");

    cout << " Insert Remove Test PASSED\n";
}

void testUnion(Set &set)
{
    ASSERT(set.getSize() == 0, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    cout << " Union Test PASSED\n";
}

void testIntersection(Set &set)
{
    ASSERT(set.getSize() == 0, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    cout << " Intersection Test PASSED\n";
}

void testDifference(Set &set)
{
    ASSERT(set.getSize() == 0, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    cout << " Difference Test PASSED\n";
}

void testIsMethods(Set &set)
{
    ASSERT(set.getSize() == 0, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    cout << " Is Test PASSED\n";
}

void testDestroy(Set &set)
{
    ASSERT(set.getSize() == 0, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    cout << " Destroy Test PASSED\n";
}

bool matchInt(void *data1, void *data2)
{
    int d1 = *(int*) data1;
    int d2 = *(int*) data2;
    return d1 == d2;
}
