#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

class Queue: public List {
public:
    Queue(): List() {}
    Queue(destroy_t destroy): List(destroy) {}
    void enqueue(void *data) { insertNext(tail, data); }
    void* dequeue(void) { return removeNext(nullptr); }
    void* peek(void) { return head ? head->data : nullptr; }
};

#endif // QUEUE_HPP