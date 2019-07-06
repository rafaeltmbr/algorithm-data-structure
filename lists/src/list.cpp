#include "../include/list.hpp"

#define CLEAR_ELEMENT(e) (e)->data = (e)->next = nullptr;

List::List(): List(nullptr) {}

List::List(destroy_t destroy)
    : size{0}
    , head{nullptr}
    , tail{nullptr}
    , destroyData{destroy}
{}

List::~List()
{
    destroy();
}

void* List::deleteHead(void)
{
    if (!head)
        return nullptr;

    ListElement *old = head;
    void *data = old->data;
    head = old->next;
    CLEAR_ELEMENT(old);
    
    delete old;
    size--;

    if (!size)
        tail = nullptr;

    return data;
}

void List::destroy(void)
{
    if (destroyData) {
        while(head) {
            destroyData(head->data);
            deleteHead();
        }
    } else {
        while(head)
            deleteHead();
    }
}

void List::insertNext(ListElement *element, void *data)
{
    ListElement* newElement = new ListElement(data);

    if (element == nullptr) {
        newElement->next = head;
        head = newElement;
    } else {
        newElement->next = element->next;
        element->next = newElement;
    }

    if (newElement->next == nullptr)
        tail = newElement;

    size++;
}

void* List::removeNext(ListElement *element)
{
    if (element == nullptr)
        return deleteHead();
    
    if (size < 1 || element == tail)
        return nullptr;

    ListElement *removedElement = element->next;
    void *data = removedElement->data;
    element->next = removedElement->next;
    delete removedElement;
    size--;

    if (element->next == nullptr)
        tail = element;
    return data;
}