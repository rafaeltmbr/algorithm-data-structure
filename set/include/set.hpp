#ifndef SET_HPP
#define SET_HPP

#include "../../list/include/list.hpp"

typedef void (*destroy_t)(void *data);
typedef bool (*match_t)(void *data1, void *data2);

class Set {
protected:
    destroy_t destroy_;
    match_t match_;
    List list;
    ListElement* getListElement(void *data);
    ListElement* getPreviousListElement(void *data);
public:
    Set();
    Set(match_t match_, destroy_t destroy_);
    ~Set();
    void setMatch(match_t match) { this->match_ = match_; }
    void setDestroy(destroy_t destroy_) { this->destroy_ = destroy_; }
    void destroy(void) { list.destroy(destroy_); }
    void destroy(destroy_t destroy_) { list.destroy(destroy_); }
    int getSize(void) { return list.getSize(); }
    bool insert(void *data);
    bool remove(void *data);
    bool union_(Set &su, Set &s);
    bool intersection(Set &si, Set &s);
    bool difference(Set &sd, Set &s);
    bool isMember(void *data);
    bool isSubset(Set &s);
    bool isEqual(Set &s);
};

#endif // SET_HPP