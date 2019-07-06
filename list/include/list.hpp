#ifndef LIST_HPP
#define LIST_HPP

class ListElement {
public:
    void* data;
    ListElement* next;

    ListElement(void *d = nullptr, ListElement *n = nullptr): data{d}, next{n} {}
    void* getData(void) { return data; }
    ListElement& getNext(void) { return *next; }
};

typedef void (*destroy_t) (void *data);

class List {
protected:
    int size;
    ListElement *head, *tail;
    destroy_t destroyData;
    void* deleteHead(void);
public:
    List();
    List(destroy_t destroy);
    ~List();
    void destroy(void);
    void setDestroy(destroy_t destroy) { destroyData = destroy; };
    void insertNext(ListElement *element, void *data);
    void* removeNext(ListElement *element);
    int getSize(void) { return size; }
    ListElement* getHead(void) { return head; }
    ListElement* getTail(void) { return tail; }
    bool isHead(const ListElement *element) { return head == element; }
    bool isTail(const ListElement *element) { return tail == element; }
};

#endif // LIST_HPP