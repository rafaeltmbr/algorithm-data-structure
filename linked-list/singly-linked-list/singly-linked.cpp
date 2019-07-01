/**
 * Doxygen comments
 * @page
 * Singly Linked List implementation.
 */

#include "singly-linked.hpp"

SinglyLinked::SinglyLinked(): SinglyLinked(nullptr) {}

SinglyLinked::SinglyLinked(destroy_t destroy)
    : size{0}
    , head{nullptr}
    , tail{nullptr}
    , destroyData{destroy}
{}

SinglyLinked::~SinglyLinked()
{
    destroy();
}

void* SinglyLinked::deleteHead(void)
{
    void *data = head->data;
    ListElement *deleted = head;
    head = head->next;
    delete deleted;
    size--;

    return data;
}

SinglyLinked& SinglyLinked::destroy(void)
{
    if (destroyData)
        while(head) {
            destroyData(head->data);
            deleteHead();
        }
    else
        while(head)
            deleteHead();

    return *this;
}

SinglyLinked& SinglyLinked::setDestroy(destroy_t destroy)
{
    destroyData = destroy;
    return *this;
}

SinglyLinked& SinglyLinked::insertNext(ListElement *element, void *data)
{
    ListElement* newElement = new ListElement(data);

    if (element == nullptr) {
        newElement->next = head;
        head = newElement;
    } else {
        newElement->next = element->next;
        element->next = newElement;
    }

    if (size == 0)
        newElement->next = nullptr;

    if (newElement->next == nullptr)
        tail = newElement;

    size++;
    return *this;
}

SinglyLinked& SinglyLinked::removeNext(ListElement *element, void **data)
{
    ListElement* removedElement;

    if (size <= 0)
        *data = nullptr;
    else if (element == nullptr)
        *data = deleteHead();
    else {
        removedElement = element->next;
        *data = removedElement->data;
        element->next = removedElement->next;
        delete removedElement;
        size--;

        if (element->next == nullptr)
            tail = element;
    }
    
    return *this;
}