#include "../include/set.hpp"

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

int Set::insert(void *data)
{

}

bool Set::remove(void *data)
{

}

bool Set::union_(Set &su, Set &s)
{

}

bool Set::intersection(Set &si, Set &s)
{

}

bool Set::difference(Set &sd, Set &s)
{

}

bool Set::isMember(void *data)
{

}

bool Set::isSubset(Set &s)
{

}

bool Set::isEqual(Set &s)
{
    
}