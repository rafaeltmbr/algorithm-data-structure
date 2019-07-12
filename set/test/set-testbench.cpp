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

void testConstructor(Set &set);
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
    testConstructor(set);
    testInsertRemove(set);
    testUnion(set);
    testIntersection(set);
    testDifference(set);
    testIsMethods(set);
    cout << "------------------------- Set SUCCEED -------------------------" << endl;
}

void testConstructor(Set &set)
{
    int i = 10;
    double d = 2.718;
    string s = "Hello";

    ASSERT(set.getSize() == 0, "getSize() failed");
    set.insertNext(nullptr, &i);
    set.insertNext(nullptr, &d);
    set.insertNext(nullptr, &s);
    ASSERT(set.getSize() == 3, "getSize() failed");

    List copy(set);
    ASSERT(set.getSize() == 3, "getSize() failed");

    ASSERT(set.removeNext(nullptr) == copy.removeNext(nullptr), "removeNext() failed");
    ASSERT(set.removeNext(nullptr) == copy.removeNext(nullptr), "removeNext() failed");
    ASSERT(set.removeNext(nullptr) == copy.removeNext(nullptr), "removeNext() failed");

    ASSERT(copy.removeNext(nullptr) == nullptr, "removeNext() failed");
    ASSERT(set.getSize() == 0, "getSize() failed");

    cout << " Constructor Test PASSED" << endl;
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
    int i1= 10, i2 = 20, i3 = 30, i4 = 40, i5 = 50, i6 = 60;
    Set s1(matchInt, nullptr), s2(matchInt, nullptr);

    ASSERT(s1.getSize() == 0, "getSize() failed");
    ASSERT(s1.insert(&i1), "insert() failed");
    ASSERT(s1.insert(&i2), "insert() failed");
    ASSERT(s1.insert(&i3), "insert() failed");
    ASSERT(s1.getSize() == 3, "getSize() failed");

    ASSERT(s2.getSize() == 0, "getSize() failed");
    ASSERT(s2.insert(&i3), "insert() failed");
    ASSERT(s2.insert(&i4), "insert() failed");
    ASSERT(s2.insert(&i5), "insert() failed");
    ASSERT(s2.getSize() == 3, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    ASSERT(set.union_(s1, s2), "union() failed");
    ASSERT(set.getSize() == 5, "getSize() failed");

    ASSERT(set.isMember(&i1), "isMember() failed");
    ASSERT(set.isMember(&i2), "isMember() failed");
    ASSERT(set.isMember(&i3), "isMember() failed");
    ASSERT(set.isMember(&i4), "isMember() failed");
    ASSERT(set.isMember(&i5), "isMember() failed");
    ASSERT(!set.isMember(&i6), "isMember() failed");

    set.destroy();
    ASSERT(set.getSize() == 0, "getSize() failed");

    s1.destroy();
    ASSERT(s1.getSize() == 0, "getSize() failed");
    
    s2.destroy();
    ASSERT(s2.getSize() == 0, "getSize() failed");

    cout << " Union Test PASSED\n";
}

void testIntersection(Set &set)
{
    int i1= 10, i2 = 20, i3 = 30, i4 = 40, i5 = 50, i6 = 60;
    Set s1(matchInt, nullptr), s2(matchInt, nullptr);

    ASSERT(s1.getSize() == 0, "getSize() failed");
    ASSERT(s1.insert(&i1), "insert() failed");
    ASSERT(s1.insert(&i2), "insert() failed");
    ASSERT(s1.insert(&i3), "insert() failed");
    ASSERT(s1.insert(&i4), "insert() failed");
    ASSERT(s1.getSize() == 4, "getSize() failed");

    ASSERT(s2.getSize() == 0, "getSize() failed");
    ASSERT(s2.insert(&i3), "insert() failed");
    ASSERT(s2.insert(&i4), "insert() failed");
    ASSERT(s2.insert(&i5), "insert() failed");
    ASSERT(s2.insert(&i6), "insert() failed");
    ASSERT(s2.getSize() == 4, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    ASSERT(set.intersection(s1, s2), "intersection() failed");
    ASSERT(set.getSize() == 2, "getSize() failed");

    ASSERT(set.isMember(&i3), "isMember() failed");
    ASSERT(set.isMember(&i4), "isMember() failed");
    ASSERT(!set.isMember(&i5), "isMember() failed");

    set.destroy();
    ASSERT(set.getSize() == 0, "getSize() failed");

    s1.destroy();
    ASSERT(s1.getSize() == 0, "getSize() failed");
    
    s2.destroy();
    ASSERT(s2.getSize() == 0, "getSize() failed");

    cout << " Intersection Test PASSED\n";
}

void testDifference(Set &set)
{
    int i1= 10, i2 = 20, i3 = 30, i4 = 40, i5 = 50;
    Set s1(matchInt, nullptr), s2(matchInt, nullptr);

    ASSERT(s1.getSize() == 0, "getSize() failed");
    ASSERT(s1.insert(&i1), "insert() failed");
    ASSERT(s1.insert(&i2), "insert() failed");
    ASSERT(s1.insert(&i3), "insert() failed");
    ASSERT(s1.insert(&i4), "insert() failed");
    ASSERT(s1.getSize() == 4, "getSize() failed");

    ASSERT(s2.getSize() == 0, "getSize() failed");
    ASSERT(s2.insert(&i3), "insert() failed");
    ASSERT(s2.insert(&i4), "insert() failed");
    ASSERT(s2.insert(&i5), "insert() failed");
    ASSERT(s2.getSize() == 3, "getSize() failed");

    ASSERT(set.getSize() == 0, "getSize() failed");
    ASSERT(set.difference(s1, s2), "difference() failed");
    ASSERT(set.getSize() == 2, "getSize() failed");

    ASSERT(set.isMember(&i1), "isMember() failed");
    ASSERT(set.isMember(&i2), "isMember() failed");
    ASSERT(!set.isMember(&i3), "isMember() failed");

    set.destroy();
    ASSERT(set.getSize() == 0, "getSize() failed");

    s1.destroy();
    ASSERT(s1.getSize() == 0, "getSize() failed");
    
    s2.destroy();
    ASSERT(s2.getSize() == 0, "getSize() failed");

    cout << " Difference Test PASSED\n";
}

void testIsMethods(Set &set)
{
    int i1= 10, i2 = 20, i3 = 30, i4 = 40;
    Set s(matchInt, nullptr);

    ASSERT(set.getSize() == 0, "getSize() failed");
    ASSERT(set.insert(&i1), "insert() failed");
    ASSERT(set.insert(&i2), "insert() failed");
    ASSERT(set.insert(&i3), "insert() failed");
    ASSERT(set.getSize() == 3, "getSize() failed");

    ASSERT(s.getSize() == 0, "getSize() failed");
    ASSERT(s.insert(&i2), "insert() failed");
    ASSERT(s.insert(&i3), "insert() failed");
    ASSERT(s.getSize() == 2, "getSize() failed");

    ASSERT(set.isSubset(s), "isSubset() failed");
    ASSERT(!set.isEqual(s), "isEqual() failed");

    ASSERT(!s.isMember(&i1), "isMember() failed");
    s.insert(&i1);
    ASSERT(s.isMember(&i1), "isMember() failed");

    ASSERT(set.isEqual(s), "isEqual() failed");
    s.insert(&i4);
    ASSERT(!set.isEqual(s), "isEqual() failed");

    set.destroy();
    ASSERT(set.getSize() == 0, "getSize() failed");

    s.destroy();
    ASSERT(s.getSize() == 0, "getSize() failed");

    cout << " isMethods Test PASSED\n";
}

bool matchInt(void *data1, void *data2)
{
    int d1 = *(int*) data1;
    int d2 = *(int*) data2;
    return d1 == d2;
}
