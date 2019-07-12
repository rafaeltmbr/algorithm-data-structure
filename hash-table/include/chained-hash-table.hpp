#ifndef CHAINED_HASH_TABLE_HPP
#define CHAINED_HASH_TABLE_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(const void *data1, const void *data2);
typedef int (*hash_t)(const void *key);

class ChainedHashTable {
protected:
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
    bool insert(void *key);
    void* remove(void *key);
    void* lookup(void *key);
    int size(void);
};

#endif // CHAINED_HASH_TABLE_HPP