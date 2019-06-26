/**
 * Doxygen comments
 * @page
 * Singly Linked List testbench.
 * <em> Build commands: 
 *   g++ singly-linked-testbench.cpp singly-linked.cpp -g -std=c++14 -Wall -o singly-linked.exe
 * </em>
 */

#include "singly-linked.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main()
{
    int *i = new int, *ix = new int;
    double *d = new double, *dx = new double;
    string *s = new string, *sx = new string;

    *i = 32;
    *d = 3.141592654;
    *s = "Okay";

    SinglyLinked list;
    list.insertNext(nullptr, i);
    list.insertNext(nullptr, d);
    list.insertNext(nullptr, s);

    list.removeNext(nullptr, (void**) &ix);
    list.removeNext(nullptr, (void**) &dx);
    list.removeNext(nullptr, (void**) &sx);

    cout << "ix: " << *ix
         << "\ndx: " << *dx
         << "\nsx: " << *sx
         << "\nlist length: " << list.getSize() << endl;

    delete i;
    delete ix;
    delete d;
    delete dx;
    delete s;
    delete sx;
}