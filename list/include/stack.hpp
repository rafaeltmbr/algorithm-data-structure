#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

class Stack: public List {
public:
    Stack(): List() {};
    Stack(destroy_t destroy): List(destroy) {};
    void push(void *data) { insertNext(nullptr, data); };
    void* pop(void) { return removeNext(nullptr); };
    void* peek(void) { return head ? head->data : nullptr; };
};

#endif // STACK_HPP