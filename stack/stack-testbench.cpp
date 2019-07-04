#include <iostream>
#include <cstdlib>
#include "stack.hpp"

using namespace std;

#define ASSERT(c, s) \
    if ( !(c) ) { \
        cout << "Assertion Failed (" << __LINE__ << "): " << s << endl; \
        exit(EXIT_FAILURE); \
    }

void testPushingPoping(Stack& stack);
void testTop(Stack& stack);
void testDestroy(Stack& stack);

int main()
{
    Stack stack;
    testPushingPoping(stack);
    testTop(stack);
    testDestroy(stack);
}

void testPushingPoping(Stack& stack)
{
    int i = 35;
    double d = 2.178;
    string s = "Okay";

    stack.push( (void*) &i);
    stack.push( (void*) &d);
    stack.push( (void*) &s);

    ASSERT( stack.size() == 3, "Wrong size");
    ASSERT( stack.pop() == &s, "Invalid pop");
    ASSERT( stack.pop() == &d, "Invalid pop");
    ASSERT( stack.pop() == &i, "Invalid pop");
    ASSERT( stack.size() == 0, "Wrong size");
}

void testTop(Stack& stack)
{
    int i = 35;
    double d = 2.178;

    stack.push( (void*) &i);
    stack.push( (void*) &d);
    
    ASSERT( stack.size() == 2, "Wrong size");
    ASSERT( stack.top() == &d, "Invalid top");
    stack.pop();
    ASSERT( stack.top() == &i, "Invalid top");
    stack.pop();
    ASSERT( stack.size() == 0, "Wrong size");
}

void destroy(void *data)
{
    *(int*) data = 10;
}

void testDestroy(Stack& stack)
{
    int i = 5;
    stack.destroy();

    stack.push( (void*) &i);
    ASSERT( stack.top() == &i, "Invaild top");
    stack.setDestroy(destroy);
    ASSERT( i == 10, "Failed on destroy");
    ASSERT( stack.size() == 0, "Invalid size");
}