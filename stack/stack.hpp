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
    StackElement *topPtr;
    destroy_t destroyData;
    int length;
    void deleteTop(void);
public:
    Stack();
    Stack(destroy_t destroyFunction);
    ~Stack();
    void push(void *data);
    void* pop(void);
    void* top(void);
    int size(void);
    void destroy(void);
    void setDestroy(destroy_t destroyFunction);
};

#endif // STACK_HPP