#ifndef LIST_HPP
#define LIST_HPP

class ListElement {
public:
    void* data;
    ListElement* next;

    ListElement(void *data = nullptr, ListElement *next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
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
    List(destroy_t destroyFunc): List() { destroyData = destroyFunc; };
    ~List();
    void destroy(void);
    void destroy(destroy_t destroyFunc);
    void setDestroy(destroy_t destroyFunc) { destroyData = destroyFunc; }
    void insertNext(ListElement *element, void *data);
    void* removeNext(ListElement *element);
    int getSize(void) { return size; }
    void* getData(ListElement *element) {return element ? element->data : nullptr; }
    ListElement* getNext(ListElement *element) {return element ? element->next : nullptr; }
    ListElement* getHead(void) { return head; }
    ListElement* getTail(void) { return tail; }
    bool isHead(const ListElement *element) { return head == element; }
    bool isTail(const ListElement *element) { return tail == element; }
};

#endif // LIST_HPP