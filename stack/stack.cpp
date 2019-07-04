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

void Stack::deleteTop(void)
{
    StackElement *below = topPtr->below;
    delete topPtr;
    topPtr = below;
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
    deleteTop();
    return d;
}

void Stack::destroy(void)
{
    while (topPtr) {
        if (destroyData)
            destroyData(topPtr->data);
        deleteTop();
        length--;
    }
}