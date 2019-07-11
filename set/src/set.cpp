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

bool Set::remove(void *data)
{
    ListElement *le = getPreviousListElement(data);

    if (le) {
        removeNext(le);
        return true;
    }

    if( (le = getHead()) && match_(le->data, data) ) {
        removeNext(nullptr);
        return true;
    }

    return false;
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

bool Set::isMember(void *data)
{
    return getListElement(data) != nullptr;
}

bool Set::isSubset(Set &s)
{
    ListElement *le = s.getHead();
    while(le) {
        if (!isMember(le->data))
            return false;
        le = le->next;
    }
    return true;
}

bool Set::isEqual(Set &s)
{
    if (size != s.getSize())
        return false;

    return isSubset(s);
}