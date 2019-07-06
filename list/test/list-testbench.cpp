/*
    g++ list-testbench.cpp ../src/list.cpp -g -std=c++14 -Wall -o list.exe
 */

#define ASSERT(cond, msg) { \
    if ( !(cond) ) { \
        std::cout << "Test failed (" << __LINE__ << "): " << msg << std::endl; \
        exit(EXIT_FAILURE); \
    } \
}

#include "../include/list.hpp"
#include <iostream> // cout, endl
#include <cstdlib>  // exit()

using namespace std;

void testInsertRemove(List &list);
void testDestruction(List &list);
void testElementCheck(List &list);
void testDestroyElement(List &list);

int main()
{
    List list;
    cout << "---------------------- List Testbench ---------------------\n";
    testInsertRemove(list);
    testDestruction(list);
    testElementCheck(list);
    testDestroyElement(list);
    cout << "-------------------- Testbench SUCCEED --------------------" << endl;
}

void testInsertRemove(List &list)
{
    int i = 32, *iptr;
    double d = 3.1416, *dptr;
    string s = "Okay", *sptr;

    list.insertNext(nullptr, &i);
    list.insertNext(nullptr, &d);
    list.insertNext(nullptr, &s);
    ASSERT(list.getSize() == 3, "List can't insert all elements.");

    sptr = (string*) list.removeNext(nullptr);
    dptr = (double*) list.removeNext(nullptr);
    iptr = (int*) list.removeNext(nullptr);
    ASSERT(&i == iptr, "Returned object mismatch.");
    ASSERT(&d == dptr, "Returned object mismatch.");
    ASSERT(&s == sptr, "Returned object mismatch.");
    ASSERT(list.getSize() == 0, "List can't free all elements.");

    cout << "Insert and Remove test PASSED" << endl;
}

#define DESTRUCTION_TIMES 10

void testDestruction(List &list)
{
    int array[DESTRUCTION_TIMES];

    for (int i=0; i < DESTRUCTION_TIMES; i++)
        list.insertNext(nullptr, array + i);
    ASSERT(list.getSize() == DESTRUCTION_TIMES, "Size mismatch.");

    list.destroy();
    ASSERT(list.getSize() == 0, "list can't be freed.");

    cout << "Destruction Test PASSED" << endl;
}

void testElementCheck(List &list)
{
    int a[] = {10, 20, 30};

    list.insertNext(nullptr, a);
    list.insertNext(nullptr, a+1);
    list.insertNext(nullptr, a+2);

    ASSERT( list.getHead()->getData() == a+2, "getHead() Failed.");
    ASSERT( list.getTail()->getData() == a, "getTail() Failed.");
    ASSERT( list.getHead()->getNext().getData() == a+1, "getNext() Failed.");

    ASSERT( list.isHead(list.getHead()), "isHead() Failed." );
    ASSERT( list.isTail(list.getTail()), "isHead() Failed." );

    ASSERT( list.getSize() == 3, "getSize() Failed.");

    list.destroy();
    cout << "Element Check Test PASSED" << endl;
}

void destroyInt(void *data)
{
    int *iptr = (int*) data;
    *iptr = 20;
}

void testDestroyElement(List &list)
{
    int *iptr = new int(10);
    list.setDestroy(destroyInt);
    list.insertNext(nullptr, iptr);
    list.destroy();
    list.setDestroy(nullptr);

    cout << "Destroy Element Test " << ( *iptr == 20 ? "PASSED" : "FAILED") << endl;
    delete iptr;
}
