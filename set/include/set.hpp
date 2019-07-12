#ifndef SET_HPP
#define SET_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(void *data1, void *data2);

class Set: public List {
protected:
    match_t match_;
    ListElement* getListElement(void *data);
    ListElement* getPreviousListElement(void *data);
public:
    Set(): List() { match_ = nullptr; };
    Set(Set &set): List(set) { match_ = set.match_; };
    Set(match_t match_, destroy_t destroy_ = nullptr): List(destroy_) { this->match_ = match_; }
    ~Set(){ match_ = nullptr; }
    bool insert(void *data);
    bool remove(void *data);
    bool union_(Set &s1, Set &s2);
    bool intersection(Set &s1, Set &s2);
    bool difference(Set &s1, Set &s2);
    bool isMember(void *data);
    bool isSubset(Set &s);
    bool isEqual(Set &s);
};

#endif // SET_HPP