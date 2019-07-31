#ifndef LIST_HPP
#define LIST_HPP

class ListElement {
public:
    void* data;
    ListElement* next;

    ListElement(void* data = nullptr, ListElement* next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
    void* getData(void) { return data; }
    ListElement& getNext(void) { return *next; }
};

typedef void (*destroy_t)(void* data);
typedef bool (*match_t)(const void* data1, const void* data2);
typedef void (*listCallback_t)(void* data, void* that);

class List {
protected:
    int size;
    ListElement *head, *tail;
    destroy_t destroyData;
    void* deleteHead(void);

public:
    bool forEachEnabled;
    match_t match = nullptr;
    List();
    List(destroy_t destroyFunc)
        : List()
    {
        destroyData = destroyFunc;
    };
    List(List& list);
    ~List();
    void destroy(void);
    void destroy(destroy_t destroyFunc);
    void setDestroy(destroy_t destroyFunc) { destroyData = destroyFunc; }
    void insertNext(ListElement* element, void* data);
    void* removeNext(ListElement* element);
    int getSize(void) const { return size; }
    void* getData(ListElement* element) { return element ? element->data : nullptr; }
    ListElement* getNext(ListElement* element) { return element ? element->next : nullptr; }
    ListElement* getHead(void) { return head; }
    ListElement* getTail(void) { return tail; }
    bool isHead(const ListElement* element) const { return head == element; }
    bool isTail(const ListElement* element) const { return tail == element; }
    void insertListNext(ListElement* element, List& list);
    int forEach(listCallback_t callbackFunction, void* that);
    ListElement* getElementByData(const void* data);
    bool hasListElement(ListElement* element);
    bool removeElementByData(const void* data);
};

#endif // LIST_HPP