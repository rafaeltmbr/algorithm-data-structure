/**
 * Doxygen comments
 * @page
 * Singly Linked List implementation.
 */

#include "singly-linked.hpp"

SinglyLinked::SinglyLinked()
{
}

SinglyLinked::SinglyLinked(void (*destroy)(void* data))
{
}

SinglyLinked::~SinglyLinked()
{
}

void SinglyLinked::destroy(void)
{
}

void SinglyLinked::insertNext(ListElement& element, void const* data)
{
}

void SinglyLinked::removeNext(ListElement& element, void** data)
{
}

int SinglyLinked::getSize(void)
{
}

ListElement& SinglyLinked::getHead(void)
{
}

ListElement& SinglyLinked::getTail(void)
{
}

bool SinglyLinked::isHead(const ListElement& element)
{
}

bool SinglyLinked::isTail(const ListElement& element)
{
}

void* SinglyLinked::getData(const ListElement& element)
{
}

void* SinglyLinked::getNext(const ListElement& element)
{
}
