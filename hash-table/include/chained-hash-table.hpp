#ifndef CHAINED_HASH_TABLE_HPP
#define CHAINED_HASH_TABLE_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(const void *data1, const void *data2);
typedef int (*hash_t)(const void *key);

class ChainedHashTable {
protected:
    int size;
    int dataSize;
    int keys;
    match_t match;
    destroy_t destroyData;
    hash_t hash;
public:
    ChainedHashTable();
    ChainedHashTable(
        hash_t hash,
        match_t matchFunc = nullptr,
        destroy_t destroyFunc = nullptr,
        int keys = 23,
        int dataSize = 4 );
    ChainedHashTable(ChainedHashTable& chtable);
    ~ChainedHashTable();
    void setDestroy(destroy_t destroyFunc) { destroyData = destroyFunc; };
    void setMatch(match_t matchFunc) { this->match = matchFunc; }
    void setHash(hash_t hashFunc) { this->hash = hashFunc; }
    void destroy(void);
    void destroy(destroy_t destroyFunc);
    bool insert(void *data);
    void* remove(void *data);
    void* lookup(void *data);
    int getSize(void) { return size; };
};

#endif // CHAINED_HASH_TABLE_HPP