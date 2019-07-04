#ifndef STACK_HPP
#define STACK_HPP

typedef void (*destroy_t) (void *data);

class StackElement {
public:
    void* data;
    StackElement* below;

    StackElement(void *data, StackElement *below)
    {
        this->data = data;
        this->below = below;
    }
};

class Stack {
    StackElement *top;
    destroy_t destroyData;
    int length;
    void deleteTop(void);
public:
    Stack();
    Stack(destroy_t destroyFunction);
    ~Stack();
    void push(void *data);
    void* pop(void);
    void* peek(void) { return top ? top->data : nullptr; };
    int size(void) { return length; };
    void destroy(void);
    void setDestroy(destroy_t destroyFunction) { destroyData=destroyFunction; };
};

#endif // STACK_HPP