#ifndef SET_HPP
#define SET_HPP

#include "../../list/include/list.hpp"

typedef void (*destroy_t)(void *data);
typedef void (*match_t)(void *data1, void *data2);

class Set {
protected:
    destroy_t destroy_;
    match_t match_;
    List list;
public:
    Set();
    Set(match_t match_, destroy_t destroy_);
    ~Set();
    void destroy(void) { list.destroy(destroy_); }
    void destroy(destroy_t destroy_) { list.destroy(destroy_); }
    int getSize(void) { return list.getSize(); }
    int insert(void *data);
    bool remove(void *data);
    bool union_(Set &su, Set &s);
    bool intersection(Set &si, Set &s);
    bool difference(Set &sd, Set &s);
    bool isMember(void *data);
    bool isSubset(Set &s);
    bool isEqual(Set &s);
};

#endif // SET_HPP