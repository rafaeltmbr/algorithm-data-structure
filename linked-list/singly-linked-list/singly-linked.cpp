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
    destroyData = nullptr;
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

void SinglyLinked::destroy(void)
{
    if (destroyData)
        while(head) {
            destroyData(head->data);
            deleteHead();
        }
    else
        while(head)
            deleteHead();
}

int SinglyLinked::insertNext(ListElement *element, void *data)
{
    ListElement* newElement = new ListElement(data);

    if (element == nullptr) {
        newElement->next = head;
        head = newElement;
    } else {
        newElement = element->next;
        element->next = newElement;
    }

    if (newElement->next == nullptr)
        tail = newElement;

    size++;
    return LIST_SUCCESS;
}

int SinglyLinked::removeNext(ListElement *element, void **data)
{
    if (size <= 0)
        return LIST_FAILURE;

    ListElement* removedElement;

    if (element == nullptr)
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

    return LIST_SUCCESS;
}