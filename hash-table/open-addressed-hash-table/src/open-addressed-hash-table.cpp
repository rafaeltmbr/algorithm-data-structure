#include "../include/open-addressed-hash-table.hpp"

int OpenAddressedHashTable::getIndex(void* data, int i)
{
    return (hash1 && hash2)
        ? (hash1(data, keys) + i * hash2(data, keys)) % keys
        : -1;
}

OpenAddressedHashTable::OpenAddressedHashTable(
    int keys,
    hash_t hash1,
    hash_t hash2,
    match_t match,
    destroy_t destroy)
{
    size = 0;
    this->keys = keys;
    this->hash1 = hash1;
    this->hash2 = hash2;
    this->match = match;
    this->destroy_ = destroy;

    if (keys < 1)
        this->keys = 23;

    empty = &empty;
    table = new void*[keys];
    for (int i = 0; i < keys; i++)
        table[i] = nullptr;
}

OpenAddressedHashTable::OpenAddressedHashTable(OpenAddressedHashTable& ohtable)
{
    keys = ohtable.keys;
    hash1 = ohtable.hash1;
    hash2 = ohtable.hash2;
    match = ohtable.match;
    destroy_ = ohtable.destroy_;

    empty = &empty;
    table = new void*[keys];
    for (int i = 0; i < keys; i++)
        table[i] = ohtable.table[i];

    size = ohtable.size;
}

OpenAddressedHashTable::~OpenAddressedHashTable()
{
    hash1 = nullptr;
    hash2 = nullptr;
    match = nullptr;
    destroy_ = nullptr;
    delete[] table;
}

void OpenAddressedHashTable::destroy(void)
{
    for (int i = 0; i < keys; i++) {
        if (table[i] != empty && table[i] && destroy_)
            destroy_(table[i]);
        table[i] = nullptr;
    }
    size = 0;
}

void OpenAddressedHashTable::destroy(destroy_t destroy)
{
    for (int i = 0; i < keys; i++) {
        if (table[i] != empty && table[i] && destroy)
            destroy(table[i]);
        table[i] = nullptr;
    }
    size = 0;
}

bool OpenAddressedHashTable::insert(void* data)
{
    if ( data == nullptr || size == keys || lookup(data) )
        return false;

    for (int i = 0, index; i < keys; i++) {
        index = getIndex(data, i);
        if (table[index] == nullptr || table[index] == empty) {
            table[index] = data;
            size++;
            return true;
        }
    }
    return false;
}

void* OpenAddressedHashTable::remove(void* data)
{
    for (int i = 0, index; i < keys; i++) {
        index = getIndex(data, i);

        if (table[index] == nullptr)
            return nullptr;

        if (table[index] != empty && match(table[index], data)) {
            void* d = table[index];
            table[index] = empty;
            size--;
            return d;
        }

    }

    return nullptr;
}

void* OpenAddressedHashTable::lookup(void* data)
{
    for (int i = 0, index; i < keys; i++) {
        index = getIndex(data, i);

        if (table[index] == nullptr)
            return nullptr;

        if ( table[index] != empty && match(table[index], data) )
            return table[index];
    }

    return nullptr;
}
