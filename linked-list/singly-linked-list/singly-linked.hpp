#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#define LIST_SUCCESS 0
#define LIST_FAILURE -1

/**
 * Doxygen comments
 * @mainpage
 * This is a implementation of a singly linked list that appears in the book
 * Mastering Algorithms with C - Kyle Loudon.
 */

class ListElement {
public:
    ListElement(void *d = nullptr, ListElement *n = nullptr): data{d}, next{n} {}
    void* data;
    ListElement* next;
};

typedef void (*destroy_t) (void *data);

class SinglyLinked {
    int size;
    ListElement *head, *tail;
    destroy_t destroyData;

public:
    SinglyLinked();
    SinglyLinked(destroy_t destroy);
    ~SinglyLinked();
    void destroy(void);
    int insertNext(ListElement *element, void *data);
    int removeNext(ListElement *element, void **data);
    int getSize(void);
    ListElement* getHead(void);
    ListElement* getTail(void);
    bool isHead(const ListElement *element);
    bool isTail(const ListElement *element);
    void* getData(ListElement *element);
    ListElement* getNext(const ListElement *element);
};

#endif // SINGLY_LINKED_LIST