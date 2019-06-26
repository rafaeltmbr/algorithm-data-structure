#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

/**
 * Doxygen comments
 * @mainpage
 * This is a implementation of a singly linked list that appears in the book
 * Mastering Algorithms with C - Kyle Loudon.
 */

class ListElement {
public:
    ListElement(): data{nullptr}, next{nullptr} {}
    ListElement(void* d): data{d}, next{nullptr} {}
    void* data;
    ListElement* next;
};

class SinglyLinked {
    int size;
    ListElement *head, *tail;
    void (*destroyData)(void *data);

public:
    SinglyLinked();
    SinglyLinked(void (*destroy)(void *data));
    ~SinglyLinked();
    void destroy(void);
    void insertNext(ListElement *element, void *data);
    void removeNext(ListElement *element, void **data);
    int getSize(void);
    ListElement* getHead(void);
    ListElement* getTail(void);
    bool isHead(const ListElement *element);
    bool isTail(const ListElement *element);
    void* getData(ListElement *element);
    ListElement* getNext(const ListElement *element);
};

#endif // SINGLY_LINKED_LIST