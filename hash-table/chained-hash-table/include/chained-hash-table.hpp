#ifndef CHAINED_HASH_TABLE_HPP
#define CHAINED_HASH_TABLE_HPP

#include "../../set/include/set.hpp"

typedef int (*hash_t)(const void *data, int keys);

class ChainedHashTable {
protected:
    int size;
    int keys;
    Set* table;
    hash_t hash;
    match_t match;
    destroy_t destroy_;

public:
    ChainedHashTable();
    ChainedHashTable(
        int keys,
        hash_t hash = nullptr,
        match_t matchFunc = nullptr,
        destroy_t destroyFunc = nullptr);
    ChainedHashTable(ChainedHashTable& chtable);
    ~ChainedHashTable();
    void setDestroy(destroy_t destroyFunc);
    void setMatch(match_t matchFunc);
    void setHash(hash_t hashFunc) { this->hash = hashFunc; }
    void destroy(void);
    void destroy(destroy_t destroyFunc);
    bool insert(void *data);
    void* remove(void *data);
    void* lookup(void *data);
    int getSize(void) { return size; };
    int getKeys(void) { return keys; };
};

#endif // CHAINED_HASH_TABLE_HPP