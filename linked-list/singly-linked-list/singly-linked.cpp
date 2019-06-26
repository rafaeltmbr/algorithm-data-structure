/**
 * Doxygen comments
 * @page
 * Singly Linked List implementation.
 */

#include "singly-linked.hpp"

SinglyLinked::SinglyLinked()
{
    size = 0;
    head = new ListElement(nullptr);
    tail = head;
    destroyData = nullptr;
}

SinglyLinked::SinglyLinked(void (*destroy)(void *data)) : SinglyLinked::SinglyLinked()
{
    destroyData = destroy;
}

SinglyLinked::~SinglyLinked()
{
    ListElement *le = head, *nx;
    while (le->next) {
        nx = le->next;
        delete le;
        le = nx;
    }
}

void SinglyLinked::destroy(void)
{
    ListElement *le = head, *nx;
    while (le->next) {
        destroyData(le->data);
        nx = le->next;
        delete le;
        le = nx;
    }
}

void SinglyLinked::insertNext(ListElement *element, void  *data)
{
    ListElement *temp;
    
    if ( !element ) {
        temp = head;
        head = new ListElement(data);
        head->next = temp;
    } else {
        temp = element->next;
        element->next = new ListElement(data);
        element->next->next = temp;

        if (!element->next->next)
            tail = element->next;
    }

    size++;
}

void SinglyLinked::removeNext(ListElement *element, void **data)
{
    ListElement *le = head;

    if (size <= 0)
        return;

    if ( !element ) {
        *data = head->data;
        le = head->next;
        delete head;
        head = le;
        size--;
    } else {
        int i;
        for (i=0; i < size && le != element; i++)
            le = le->next;
        *data = i < size ? le->data : nullptr;
        size--;
    }
}

int SinglyLinked::getSize(void)
{
    return size;
}

ListElement* SinglyLinked::getHead(void)
{
    return head;
}

ListElement* SinglyLinked::getTail(void)
{
    return tail;
}

bool SinglyLinked::isHead(const ListElement *element)
{
    return element == head;
}

bool SinglyLinked::isTail(const ListElement *element)
{
    return element == tail;
}

void* SinglyLinked::getData(ListElement *element)
{
    return element->data;
}

ListElement* SinglyLinked::getNext(const ListElement *element)
{
    ListElement *le = head;
    for (int i=0; i < size; i++) {
        if (element == le)
            return le->next;
    }
    return nullptr;
}