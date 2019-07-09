/**
 * Buil commands:
 *  g++ set-testbench.cpp ../src/set.cpp ../../list/src/list.cpp -g -Wall -std=c++14 -o set.exe
 */
#include "../include/set.hpp"
#include <iostream>

using namespace std;

void testInsertRemove(Set &set);
void testUnion(Set &set);
void testIntersection(Set &set);
void testDifference(Set &set);
void testIsMethods(Set &set);
void testDestroy(Set &set);

int main()
{
    cout << "------------------------ Set Testbench ------------------------\n";
    Set set;
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

}

void testUnion(Set &set)
{

}

void testIntersection(Set &set)
{

}

void testDifference(Set &set)
{

}

void testIsMethods(Set &set)
{

}

void testDestroy(Set &set)
{

}