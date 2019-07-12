#include "../include/set.hpp"

ListElement* Set::getListElement(void *data)
{
    ListElement *le = getHead();
    while(le) {
        if ( match_(le->data, data) )
            return le;
        le = le->next;
    }
    return nullptr;
}

ListElement* Set::getPreviousListElement(void *data)
{
    ListElement *le = getHead();
    if (!le || match_(le->data, data) )
        return nullptr;

    while(le->next) {
        if ( match_(le->next->data, data) )
            return le;
        le = le->next;
    }
    return nullptr;
}

bool Set::insert(void *data)
{
    if (isMember(data))
        return false;

    insertNext(nullptr, data);
    return true;
}

void* Set::remove(void *data)
{
    ListElement *le = getPreviousListElement(data);
    void *d;

    if (le) {
        d = le->next->data;
        removeNext(le);
        return d;
    }

    if( (le = getHead()) && match_(le->data, data) ) {
        d = le->data;
        removeNext(nullptr);
        return d;
    }

    return nullptr;
}

bool Set::union_(Set &s1, Set &s2)
{
    ListElement *le = s1.getHead();
    while(le) {
        insert(le->data);
        le = le->next;
    }

    le = s2.getHead();
    while(le) {
        insert(le->data);
        le = le->next;
    }

    return true;
}

bool Set::intersection(Set &s1, Set &s2)
{
    ListElement *le = s1.getHead();
    while(le) {
        if (s2.isMember(le->data))
            insert(le->data);
        le = le->next;
    }
    return true;
}

bool Set::difference(Set &s1, Set &s2)
{
    ListElement *le = s1.getHead();
    while(le) {
        if (!s2.isMember(le->data))
            insert(le->data);
        le = le->next;
    }
    return true;
}

void* Set::isMember(void *data)
{
    ListElement *d = getListElement(data);
    return d ? d->data : d;
}

bool Set::isSubset(Set &s)
{
    if (size < s.size)
        return false;

    for (ListElement *le = s.getHead(); le; le = le->next)
        if (!isMember(le->data))
            return false;
    return true;
}

bool Set::isEqual(Set &s)
{
    if (size != s.getSize())
        return false;

    return isSubset(s);
}
