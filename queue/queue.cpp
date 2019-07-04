#include "queue.hpp"

Queue::Queue()
{
    head = nullptr;
    tail = nullptr;
    destroyData = nullptr;
    length = 0;
}

Queue::Queue(destroy_t destroyFunction): Queue()
{
    destroyData = destroyFunction;
}

void Queue::deleteHead(void)
{
    QueueElement *next = head->next;
    delete head;
    head = next;
}

void Queue::enqueue(void *data)
{
    QueueElement *qe = new QueueElement(data);
    if (!head)
        head = qe;
    else
        tail->next = qe;
    tail = qe;
    length++;
}

void* Queue::dequeue(void)
{
    if (!head)
        return nullptr;
    void *data = head->data;
    deleteHead();
    length--;
    return data;
}

void Queue::destroy(void)
{
    while (head) {
        if (destroyData)
            destroyData(head->data);
        deleteHead();
        length--;
    }
}