/*
Built commands:
  g++ queue-testbench.cpp ../src/list.cpp -Wall -g -std=c++14 -o queue.exe
*/

#include "../include/queue.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

#define ASSERT(c, s) \
    if ( !(c) ) { \
        cout << "Assertion failed (" << __LINE__ << "): " << s << endl; \
        exit(EXIT_FAILURE); \
    }

void testEnqueueDequeue(Queue &queue);
void testPeek(Queue &queue);
void testDestroy(Queue &queue);

int main()
{
    Queue queue;
    cout << "---------------------- Queue Testbench ---------------------\n";
    testEnqueueDequeue(queue);
    testPeek(queue);
    testDestroy(queue);
    cout << "-------------------- Testbench SUCCEED --------------------" << endl;
}

void testEnqueueDequeue(Queue &queue)
{
    int i = 11;
    double d = 1.23456;
    string s = "Aloha";

    ASSERT(queue.getSize() == 0, "Queue must be empty");
    queue.enqueue( (void*) &i);
    queue.enqueue( (void*) &d);
    queue.enqueue( (void*) &s);

    ASSERT( queue.getSize() == 3, "Queue size failed");
    ASSERT( queue.dequeue() == &i, "Dequeue failed");
    ASSERT( queue.dequeue() == &d, "Dequeue failed");
    ASSERT( queue.dequeue() == &s, "Dequeue failed");
    ASSERT( queue.getSize() == 0, "Queue size failed");

    cout << "Enqueue and Dequeue Test SUCCEED" << endl;
}

void testPeek(Queue &queue)
{
    int i = 11;
    double d = 1.23456;

    ASSERT(queue.getSize() == 0, "Queue must be empty");
    queue.enqueue( (void*) &i);
    queue.enqueue( (void*) &d);
    ASSERT(queue.getSize() == 2, "Queue size failed");

    ASSERT(queue.peek() == &i, "Peek failed");
    queue.dequeue();
    ASSERT(queue.peek() == &d, "Peek failed");
    queue.dequeue();
    ASSERT(queue.getSize() == 0, "Queue size failed");

    cout << "Peek Test SUCCEED" << endl;
}

void destroy(void *data)
{
    int *d = (int*) data;
    *d = (*d) * 2;
}

void testDestroy(Queue &queue)
{
    int i = 15;
    ASSERT(queue.getSize() == 0, "Queue must be empty");
    queue.setDestroy(destroy);

    queue.enqueue( (void*) &i );
    queue.destroy();
    ASSERT(i == 30, "Destroy failed");
    ASSERT(queue.getSize() == 0, "Queue size failed");

    cout << "Destroy Test SUCCEED" << endl;
}
