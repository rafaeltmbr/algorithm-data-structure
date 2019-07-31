#include "../include/list.hpp"

#define CLEAR_ELEMENT(e) (e)->data = (e)->next = nullptr;

List::List()
{
    size = 0;
    head = nullptr;
    tail = nullptr;
    destroyData = nullptr;
}

List::List(List& list)
    : List()
{
    destroyData = list.destroyData;
    ListElement* le = list.head;
    if (!le)
        return;

    insertNext(nullptr, le->data);

    while (le->next) {
        insertNext(tail, le->next->data);
        le = le->next;
    }
}

List::~List()
{
    destroy();
}

void* List::deleteHead(void)
{
    if (!head)
        return nullptr;

    ListElement* old = head;
    void* data = old->data;
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
        while (head) {
            destroyData(head->data);
            deleteHead();
        }
    } else {
        while (head)
            deleteHead();
    }
}

void List::destroy(destroy_t destroyFunc)
{
    while (head) {
        destroyFunc(head->data);
        deleteHead();
    }
}

void List::insertNext(ListElement* element, void* data)
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

void* List::removeNext(ListElement* element)
{
    if (!element)
        return deleteHead();

    if (!element->next)
        return nullptr;

    ListElement* removedElement = element->next;
    void* data = removedElement->data;
    element->next = removedElement->next;
    delete removedElement;
    size--;

    if (element->next == nullptr)
        tail = element;
    return data;
}

void List::insertListNext(ListElement* element, List& list)
{
    destroyData = list.destroyData;
    ListElement* prev = element;
    ListElement* le = list.head;
    while (le) {
        insertNext(prev, le->data);
        prev = prev ? prev->next : head;
        le = le->next;
    }
}

int List::forEach(listCallback_t callbackFunction, void* that)
{
    int loopCount = 0;
    forEachEnabled = true;
    for (ListElement* le = head; forEachEnabled && le != nullptr; le = le->next, loopCount++)
        callbackFunction(le->data, that);
    return loopCount;
}

ListElement* List::getElementByData(const void* data)
{
    if (match) {
        for (ListElement* le = head; le != nullptr; le = le->next)
            if (match(data, le->data))
                return le;
    } else {
        for (ListElement* le = head; le != nullptr; le = le->next)
            if (data == le->data)
                return le;
    }
    return nullptr;
}

bool List::hasListElement(ListElement* element)
{
    for (ListElement* le = head; le != nullptr; le = le->next)
        if (element == le)
            return true;
    return false;
}

void* List::removeElementByData(const void* data)
{
    ListElement *prev = nullptr;
    if (match) {
        for (ListElement* le = head; le != nullptr; le = le->next)
            if (match(data, le->data))
                return removeNext(prev);
    } else {
        for (ListElement* le = head; le != nullptr; le = le->next)
            if (data == le->data)
                return removeNext(prev);
    }
    return nullptr;
}