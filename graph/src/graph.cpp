#include "../include/graph.hpp"

GraphVertex::GraphVertex(void* data, match_t match)
{
    this->data = data;
    this->match = match;
}

GraphVertex::GraphVertex(GraphVertex& graphVertex)
{
    data = graphVertex.data;
    edges.insertListNext(nullptr, graphVertex.edges);
}

bool GraphVertex::insertEdge(void* data)
{
    if (!data || !match)
        return false;

    ListElement* le = edges.getHead();
    while (le)
        if (match(data, le->data))
            return false;

    edges.insertNext(nullptr, data);
    return true;
}

void* GraphVertex::removeEdge(void* data)
{
    if (!data || !match)
        return nullptr;

    ListElement* prev = nullptr;
    ListElement* le = edges.getHead();
    while (le) {
        if (match(data, le->getData()))
            return edges.removeNext(prev);
        prev = le;
        le = edges.getNext(le);
    }
    return nullptr;
}

void* GraphVertex::getEdge(void* data)
{
    if (!data || !match)
        return nullptr;

    ListElement* le = edges.getHead();
    while (le)
        if (match(data, le->data))
            return le->data;

    return nullptr;
}

Graph::Graph(match_t match, destroy_t destroyFunc)
{
    this->match = match;
    this->destroyFunc = destroyFunc;
}

Graph::Graph(Graph& graph)
{
    match = graph.match;
    destroyFunc = graph.destroyFunc;
    edgesCount = graph.edgesCount;

    ListElement* prev = nullptr;
    ListElement* le = graph.vertexList.getHead();
    while (le && le->data) {
        vertexList.insertNext(prev, new GraphVertex(*(GraphVertex*)le->data));
        prev = prev ? prev->next : vertexList.getHead();
        le = le->next;
    }
}

Graph::~Graph(void)
{
    destroy();
}

void Graph::destroy(void)
{
    if (destroyFunc)
        while (vertexList.getSize()) {
            GraphVertex* vertex = (GraphVertex*)vertexList.removeNext(nullptr);
            destroyFunc(vertex->getData());
            delete vertex;
        }
    else
        while (vertexList.getSize())
            delete (GraphVertex*)vertexList.removeNext(nullptr);

    match = nullptr;
    destroyFunc = nullptr;
    edgesCount = 0;
}

bool Graph::insertVertex(void* data)
{
    if (!data || !match)
        return false;

    ListElement* le = vertexList.getHead();
    while (le && le->data)
        if (match(data, ((GraphVertex*)le->data)->data))
            return false;

    vertexList.insertNext(nullptr, data);
    return true;
}

void* Graph::removeVertex(void* data)
{
    if (!data || !match)
        return nullptr;

    ListElement* prev = nullptr;
    ListElement* le = vertexList.getHead();
    while (le) {
        if (match(data, le->data))
            return vertexList.removeNext(prev);
        prev = le;
        le = le->next;
    }
    return nullptr;
}

bool Graph::insertEdge(void* fromVertexData, void* toVertexData)
{
    if (!fromVertexData || !toVertexData || !match)
        return false;

    GraphVertex *fromVertex = getVertex(fromVertexData);
    GraphVertex *toVertex = getVertex(toVertexData);
    if (!fromVertex || !toVertex)
        return false;

    edgesCount++;
    fromVertex->insertEdge(toVertexData);
    return true;
    
}

bool Graph::removeEdge(void* fromVertexData, void* toVertexData)
{
    return false;
}

const List* Graph::getAdjacencyList(const void* data)
{
    return nullptr;
}

bool Graph::isAdjacent(const void* vertex, const void* adjacentVertex)
{
    return false;
}

GraphVertex* Graph::getVertex(const void* data)
{
    if (!data || !match)
        return nullptr;
 
    ListElement *le = vertexList.getHead();
    while (le && le->data) {
        if (match(data, ((GraphVertex*)le->data)->data))
            return (GraphVertex*) le->data;
        le = le->next;
    }

    return nullptr;
}
