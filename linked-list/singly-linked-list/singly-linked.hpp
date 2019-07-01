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
    void* data;
    ListElement* next;

    ListElement(void *d = nullptr, ListElement *n = nullptr): data{d}, next{n} {}
    void* getData(void) { return data; }
    ListElement& getNext(void) { return *next; }
};

typedef void (*destroy_t) (void *data);

class SinglyLinked {
    int size;
    ListElement *head, *tail;
    destroy_t destroyData;
    void* deleteHead(void);
public:
    SinglyLinked();
    SinglyLinked(destroy_t destroy);
    ~SinglyLinked();
    void destroy(void);
    void setDestroy(destroy_t destroy) { destroyData = destroy; }
    int insertNext(ListElement *element, void *data);
    int removeNext(ListElement *element, void **data);
    int getSize(void) { return size; }
    ListElement* getHead(void) { return head; }
    ListElement* getTail(void) { return tail; }
    bool isHead(const ListElement *element) { return head == element; }
    bool isTail(const ListElement *element) { return tail == element; }
};

#endif // SINGLY_LINKED_LIST