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
    if (size <= 0)
        return;

    ListElement *le = head, *nx;

    while (le->next) {
        nx = le->next;
        delete le;
        le = nx;
    }
}

void SinglyLinked::destroy(void)
{
    if (size <= 0)
        return;

    ListElement *le = head, *nx;

    if (destroyData) {
        for (; size > 0; size--) {
            destroyData(le->data);
            nx = le->next;
            delete le;
            le = nx;
        }
    } else {
        for (; size > 0; size--) {
            nx = le->next;
            delete le;
            le = nx;
        }
    }
}

int SinglyLinked::insertNext(ListElement* element, void* data)
{
    ListElement* temp;

    if (size == 0) {
        head = new ListElement(data);
        tail = head;
    } else if (!element) {
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
    return LIST_SUCCESS;
}

int SinglyLinked::removeNext(ListElement* element, void** data)
{
    if (size <= 0)
        return LIST_FAILURE;

    ListElement* le = head;

    if (!element) {
        *data = head->data;
        le = head->next;
        delete head;
        head = le;
    } else {
        int i;
        for (i = 0; i < size && le != element; i++)
            le = le->next;
        *data = i < size ? le->data : nullptr;
    }
    size--;
    return LIST_SUCCESS;
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

bool SinglyLinked::isHead(const ListElement* element)
{
    return element == head;
}

bool SinglyLinked::isTail(const ListElement* element)
{
    return element == tail;
}

void* SinglyLinked::getData(ListElement* element)
{
    return element->data;
}

ListElement* SinglyLinked::getNext(const ListElement* element)
{
    ListElement* le = head;
    for (int i = 0; i < size; i++) {
        if (element == le)
            return le->next;
    }
    return nullptr;
}