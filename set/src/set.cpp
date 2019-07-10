#include "../include/set.hpp"

ListElement* Set::getListElement(void *data)
{
    ListElement *le = list.getHead();
    while(le) {
        if ( match_(le->data, data) )
            return le;
        le = le->next;
    }
    return nullptr;
}

ListElement* Set::getPreviousListElement(void *data)
{
    ListElement *le = list.getHead();
    if (!le || match_(le->data, data) )
        return nullptr;

    while(le->next) {
        if ( match_(le->next->data, data) )
            return le;
        le = le->next;        
    }
    return nullptr;
}

Set::Set()
{
    this->destroy_ = nullptr;
    this->match_ = nullptr;
    this->list = nullptr;
}

Set::Set(match_t match_, destroy_t destroy_)
{
    this->match_ = match_;
    this->destroy_ = destroy_;
}

Set::~Set()
{
    list.destroy(destroy_);
    destroy_ = nullptr;
    match_ = nullptr;
    list = nullptr;
}

bool Set::insert(void *data)
{
    if (getListElement(data))
        return false;
    
    list.insertNext(nullptr, data);
    return true;
}

bool Set::remove(void *data)
{
    ListElement *le = getPreviousListElement(data);

    if (le) {
        list.removeNext(le);
        return true;
    }

    if( (le = list.getHead()) && match_(le->data, data) ) {
        list.removeNext(nullptr);
        return true;
    }

    return false;
}

bool Set::union_(Set &su, Set &s)
{

    return false;
}

bool Set::intersection(Set &si, Set &s)
{

    return false;
}

bool Set::difference(Set &sd, Set &s)
{

    return false;
}

bool Set::isMember(void *data)
{
    return getListElement(data) != nullptr;
}

bool Set::isSubset(Set &s)
{
    
    return false;
}

bool Set::isEqual(Set &s)
{
    
    return false;
}