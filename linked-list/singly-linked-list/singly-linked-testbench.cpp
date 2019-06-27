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
    int i, *iptr;
    double d, *dptr;
    string s, *sptr;

    i = 32;
    d = 3.141592654;
    s = "Okay";

    SinglyLinked list;
    list.insertNext(nullptr, &i);
    list.insertNext(nullptr, &d);
    list.insertNext(nullptr, &s);

    cout << "list length after insertions: " << list.getSize() << "\n\n";

    list.removeNext(nullptr, (void**) &sptr);
    list.removeNext(nullptr, (void**) &dptr);
    list.removeNext(nullptr, (void**) &iptr);

    cout << "ix: " << *iptr
         << "\ndx: " << *dptr
         << "\nsx: " << *sptr << "\n\n";

    cout << "list length after removes: " << list.getSize() << endl;
}