#ifndef OPEN_ADDRESSED_HASH_TABLE_HPP
#define OPEN_ADDRESSED_HASH_TABLE_HPP

typedef void (*destroy_t)(void *data);
typedef bool (*match_t)(const void *data1, const void *data2);
typedef int (*hash_t)(const void *data, int keys);

class OpenAddressedHashTable {
protected:
    int keys;
    int size;
    void **table;
    match_t match;
    destroy_t destroy_;
    hash_t hash1, hash2;
public:
    OpenAddressedHashTable(
        int keys,
        hash_t hash1 = nullptr,
        hash_t hash2 = nullptr,
        match_t match = nullptr,
        destroy_t destroy = nullptr);
    OpenAddressedHashTable(OpenAddressedHashTable &ohtable);
    ~OpenAddressedHashTable();
    void destroy(void);
    void destroy(destroy_t destroy);
    void setMatch(match_t match) { this->match = match; };
    void setHash1(hash_t hash1) { this->hash1 = hash1; };
    void setHash2(hash_t hash2) { this->hash2 = hash2; };
    void setDestroy(destroy_t destroy) { this->destroy_ = destroy; };
    bool insert(void *data);
    void* remove(void *data);
    void* lookup(void *data);
    int getSize(void) { return size; };
    int getKeys(void) { return keys; };
};

#endif // OPEN_ADDRESSED_HASH_TABLE_HPP