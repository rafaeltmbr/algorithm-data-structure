/**
 * Doxygen comments
 * @page
 * Singly Linked List testbench.
 * <em> Build commands:
 *   g++ singly-linked-testbench.cpp singly-linked.cpp -g -std=c++14 -Wall -o singly-linked.exe
 * </em>
 */

#define ASSERT(cond, msg) { \
    if ( !(cond) ) { \
        std::cout << "Test failed (" << __LINE__ << "): " << msg << std::endl; \
        exit(EXIT_FAILURE); \
    } \
}

#include "singly-linked.hpp"
#include <iostream> // cout, endl
#include <cstdlib>  // exit()

using namespace std;
SinglyLinked list;

void testInsertRemove(void);
void testDestruction(void);
void testElementCheck(void);
void testDestroyElement(void);

int main()
{
    testInsertRemove();
    testDestruction();
    testElementCheck();
    testDestroyElement();
}

void testInsertRemove(void)
{
    int i = 32, *iptr;
    double d = 3.1416, *dptr;
    string s = "Okay", *sptr;

    list.insertNext(nullptr, &i);
    list.insertNext(nullptr, &d);
    list.insertNext(nullptr, &s);
    ASSERT(list.getSize() == 3, "List can't insert all elements.");

    list.removeNext(nullptr, (void**) &sptr);
    list.removeNext(nullptr, (void**) &dptr);
    list.removeNext(nullptr, (void**) &iptr);
    ASSERT(&i == iptr, "Returned object mismatch.");
    ASSERT(&d == dptr, "Returned object mismatch.");
    ASSERT(&s == sptr, "Returned object mismatch.");
    ASSERT(list.getSize() == 0, "List can't free all elements.");

    cout << "Insert and Remove test PASSED" << endl;
}

#define DESTRUCTION_TIMES 10

void testDestruction(void)
{
    int array[DESTRUCTION_TIMES];

    for (int i=0; i < DESTRUCTION_TIMES; i++)
        list.insertNext(nullptr, array + i);
    ASSERT(list.getSize() == DESTRUCTION_TIMES, "Size mismatch.");

    list.destroy();
    ASSERT(list.getSize() == 0, "list can't be freed.");

    cout << "Destruction Test PASSED" << endl;
}

void testElementCheck(void)
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

void testDestroyElement(void)
{
    int *iptr = new int(10);
    list.setDestroy(destroyInt).insertNext(nullptr, iptr).destroy().setDestroy(nullptr);

    cout << "Destroy Element Test " << ( *iptr == 20 ? "PASSED" : "FAILED") << endl;
    delete iptr;
}
