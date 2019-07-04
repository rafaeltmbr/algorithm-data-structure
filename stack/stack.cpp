#include "stack.hpp"

Stack::Stack()
{
    topPtr = nullptr;
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

void Stack::push(void *data)
{
    StackElement *se = new StackElement(data, topPtr ? topPtr : nullptr);
    topPtr = se;
    length++;
}

void* Stack::pop(void)
{
    if (length < 1)
        return nullptr;

    length--;
    void *d = topPtr->data;
    StackElement* below = topPtr->below;
    delete topPtr;
    topPtr = below;
    return d;
}

void* Stack::top(void)
{
    return topPtr->data;
}

int Stack::size(void)
{
    return length;
}

void Stack::destroy(void)
{
    StackElement *below;
    while (topPtr) {
        if (destroyData)
            destroyData(topPtr->data);
        below = topPtr->below;
        delete topPtr;
        topPtr = below;
        length--;
    }
}

void Stack::setDestroy(destroy_t destroyFunction)
{
    destroyData = destroyFunction;
}
