#ifndef QUEUE_HPP
#define QUEUE_HPP

typedef void (*destroy_t) (void *data);

class QueueElement {
public:
    void *data;
    QueueElement *next;

    QueueElement()
    {
        data = nullptr;
        next = nullptr;
    }

    QueueElement(void *data)
    {
        this->data = data;
        next = nullptr;
    }
};

class Queue {
    QueueElement *head, *tail;
    destroy_t destroyData;
    int length;
    void deleteHead(void);
public:
    Queue();
    Queue(destroy_t);
    void enqueue(void *data);
    void* dequeue(void);
    void* peek(void) { return head ? head->data : nullptr; }
    int size(void) { return length; }
    void destroy(void);
    void setDestroy(destroy_t destroyFunc) { destroyData = destroyFunc; }
};

#endif // QUEUE_HPP