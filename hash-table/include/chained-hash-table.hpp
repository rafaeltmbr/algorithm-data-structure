#ifndef CHAINED_HASH_TABLE_HPP
#define CHAINED_HASH_TABLE_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(const void *data1, const void *data2);
typedef int (*hash_t)(const void *key);

class ChainedHashTable {
protected:
    int size;
    match_t match;
    destroy_t destroyData;
    hash_t hash;
public:
    ChainedHashTable();
    ChainedHashTable(hash_t, match_t = nullptr, destroy_t = nullptr);
    ChainedHashTable(ChainedHashTable&);
    ~ChainedHashTable();
    void setDestroy(destroy_t destroyFunc) {destroyData = destroyFunc; };
    void setMatch(match_t match) { this->match = match; }
    void setHash(hash_t hash) { this->hash = hash; }
    void destroy(void);
    void destroy(destroy_t);
    bool insert(void *data);
    void* remove(void *data);
    void* lookup(void *data);
    int getSize(void);
};

#endif // CHAINED_HASH_TABLE_HPP