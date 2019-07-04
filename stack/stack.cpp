#include "stack.hpp"

Stack::Stack()
{
    top = nullptr;
    destroyData = nullptr;
    length = 0;
}

Stack::Stack(destroy_t destroyFunction): Stack()
{
    destroyData = destroyFunction;
}

Stack::~Stack()
{
    destroyData = nullptr;
    destroy();
}

void Stack::deleteTop(void)
{
    StackElement *below = top->below;
    delete top;
    top = below;
}

void Stack::push(void *data)
{
    StackElement *se = new StackElement(data, top ? top : nullptr);
    top = se;
    length++;
}

void* Stack::pop(void)
{
    if (length < 1)
        return nullptr;

    length--;
    void *d = top->data;
    deleteTop();
    return d;
}

void Stack::destroy(void)
{
    while (top) {
        if (destroyData)
            destroyData(top->data);
        deleteTop();
        length--;
    }
}