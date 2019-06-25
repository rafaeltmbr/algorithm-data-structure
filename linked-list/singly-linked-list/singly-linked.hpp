#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

/**
 * Doxygen comments
 * @mainpage
 * This is a implementation of a singly linked list that appears in the book
 * Mastering Algorithms with C - Kyle Loudon.
 */

struct ListElement {
    void* data;
    ListElement* next;
};

class SinglyLinked {
    int size = 0;
    ListElement* head = nullptr;
    ListElement* tail = nullptr;
    void (*destroyData)(void* data);

public:
    SinglyLinked();
    SinglyLinked(void (*destroy)(void* data));
    ~SinglyLinked();
    void destroy(void);
    void insertNext(ListElement& element, void const* data);
    void removeNext(ListElement& element, void** data);
    int getSize(void);
    ListElement& getHead(void);
    ListElement& getTail(void);
    bool isHead(const ListElement& element);
    bool isTail(const ListElement& element);
    void* getData(const ListElement& element);
    void* getNext(const ListElement& element);
};

#endif // SINGLY_LINKED_LIST