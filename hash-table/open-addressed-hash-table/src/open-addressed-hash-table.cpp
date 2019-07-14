#include "../include/open-addressed-hash-table.hpp"

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
    for (int i = 0; size > 0 && i < keys; i++) {
        if (table[i]) {
            if (destroy_)
                destroy_(table[i]);
            table[i] = nullptr;
            size--;
        }
    }
}

void OpenAddressedHashTable::destroy(destroy_t destroy)
{
    for (int i = 0; size > 0 && i < keys; i++) {
        if (table[i]) {
            if (destroy)
                destroy(table[i]);
            table[i] = nullptr;
            size--;
        }
    }
}

bool OpenAddressedHashTable::insert(void* data)
{
    if (lookup(data))
        return false;

    for (int i = 0, index; i < keys; i++) {
        index = (hash1(data, keys) + i * hash2(data, keys)) % keys;
        if (table[index] == nullptr) {
            table[index] = data;
            size++;
            return true;
        }
    }
    return false;
}

void* OpenAddressedHashTable::remove(void* data)
{
    void* d = nullptr;

    for (int i = 0, index; i < keys; i++) {
        index = (hash1(data, keys) + i * hash2(data, keys)) % keys;
        if (match(table[index], data)) {
            d = table[index];
            table[index] = nullptr;
            size--;
            break;
        } else if (table[index] == nullptr)
            break;
    }

    return d;
}

void* OpenAddressedHashTable::lookup(void* data)
{
    for (int i = 0, index; i < keys; i++) {
        index = (hash1(data, keys) + i * hash2(data, keys)) % keys;
        if (match(table[index], data))
            return table[index];
        else if (table[index] == nullptr)
            return nullptr;
    }
    return nullptr;
}
