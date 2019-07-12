#include "../include/chained-hash-table.hpp"

ChainedHashTable::ChainedHashTable()
{
    size = 0;
    keys = 23;
    hash = nullptr;
    match = nullptr;
    destroy_ = nullptr;
    table = new Set[keys];
}

ChainedHashTable::ChainedHashTable(
    int keys,
    hash_t hash,
    match_t matchFunc,
    destroy_t destroyFunc)
{
    size = 0;
    this->hash = hash;
    match = matchFunc;
    destroy_ = destroyFunc;

    if (keys < 1)
        keys = 23;
    this->keys = keys;

    table = new Set[keys];
    setMatch(matchFunc);
    setDestroy(destroyFunc);
}

ChainedHashTable::ChainedHashTable(ChainedHashTable& chtable)
{
    keys = chtable.keys;
    hash = chtable.hash;
    table = new Set[keys];
    setMatch(chtable.match);
    setDestroy(chtable.destroy_);

    ListElement *le;
    for (int i=0; i < chtable.keys; i++) {
        le = chtable.table[i].getHead();
        while(le) {
            insert(le->data);
            le = le->next;
        }
    }
}

ChainedHashTable::~ChainedHashTable()
{
    delete[] table;
}

void ChainedHashTable::setDestroy(destroy_t destroyFunc)
{
    destroy_ = destroyFunc;

    if (!destroyFunc)
        return;

    for (int i=0; i < keys; i++)
        table[i].setDestroy(destroyFunc);

}

void ChainedHashTable::setMatch(match_t matchFunc)
{
    match = matchFunc;

    if (!matchFunc)
        return;

    for (int i=0; i < keys; i++)
        table[i].setMatch(matchFunc);
}

void ChainedHashTable::destroy(void)
{
    for (int i=0; i < keys; i++) {
        size -= table[i].getSize();
        table[i].destroy();
    }
}

void ChainedHashTable::destroy(destroy_t destroyFunc)
{
    for (int i=0; i < keys; i++) {
        size -= table[i].getSize();
        table[i].destroy(destroyFunc);
    }
}

bool ChainedHashTable::insert(void *data)
{
    if (!hash)
        return false;

    int index = hash(data, keys);

    if ( table[index].insert(data) ) {
        size++;
        return true;
    }

    return false;
}

void* ChainedHashTable::remove(void *data)
{
    if (!hash)
        return nullptr;

    int index = hash(data, keys);

    void *d = table[index].remove(data);

    if (d)
        size--;

    return d;
}

void* ChainedHashTable::lookup(void *data)
{
    if (!hash)
        return nullptr;

    int index = hash(data, keys);
    return table[index].isMember(data);
}
