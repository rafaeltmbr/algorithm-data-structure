/*
Build commands:
    g++ stack-testbench.cpp ../src/list.cpp -Wall -g -std=c++14 -o stack.exe
*/

#include <iostream>
#include <cstdlib>
#include "../include/stack.hpp"

using namespace std;

#define ASSERT(c, s) \
    if ( !(c) ) { \
        cout << "Assertion Failed (" << __LINE__ << "): " << s << endl; \
        exit(EXIT_FAILURE); \
    }

void testPushingPoping(Stack &stack);
void testPeek(Stack &stack);
void testDestroy(Stack &stack);

int main()
{
    Stack stack;
    cout << "---------------------- Stack Testbench ---------------------\n";
    testPushingPoping(stack);
    testPeek(stack);
    testDestroy(stack);
    cout << "-------------------- Testbench SUCCEED --------------------" << endl;
}

void testPushingPoping(Stack &stack)
{
    int i = 35;
    double d = 2.178;
    string s = "Okay";

    stack.push( (void*) &i);
    stack.push( (void*) &d);
    stack.push( (void*) &s);

    ASSERT( stack.getSize() == 3, "Wrong size");
    ASSERT( stack.pop() == &s, "Invalid pop");
    ASSERT( stack.pop() == &d, "Invalid pop");
    ASSERT( stack.pop() == &i, "Invalid pop");
    ASSERT( stack.getSize() == 0, "Wrong size");

    cout << "Pushing and Poping Test SUCCEED" << endl;
}

void testPeek(Stack &stack)
{
    int i = 35;
    double d = 2.178;

    stack.push( (void*) &i);
    stack.push( (void*) &d);

    ASSERT( stack.getSize() == 2, "Wrong size");
    ASSERT( stack.peek() == &d, "Invalid peek");
    stack.pop();
    ASSERT( stack.peek() == &i, "Invalid peek");
    stack.pop();
    ASSERT( stack.getSize() == 0, "Wrong size");

    cout << "Peek Test SUCCEED" << endl;
}

void destroy(void *data)
{
    int *d = (int*) data;
    *d = (*d) * 2;
}

void testDestroy(Stack &stack)
{
    int i = 5;

    stack.push( (void*) &i);
    ASSERT( stack.peek() == &i, "Invaild peek");
    stack.destroy(destroy);
    
    ASSERT( i == 10, "Failed on destroy");
    ASSERT( stack.getSize() == 0, "Invalid size");

    cout << "Destroy SUCCEED" << endl;
}
