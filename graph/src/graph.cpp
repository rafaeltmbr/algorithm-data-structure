#include "../include/graph.hpp"

GraphVertex::GraphVertex(GraphVertex& vertex)
{
    data = vertex.data;
    edges.insertListNext(nullptr, vertex.edges);
}

bool GraphVertex::insertEdge(GraphVertex& vertex)
{
    ListElement* le = edges.getHead();
    while (le) {
        if (&vertex == le->data)
            return false;
        le = le->next;
    }

    edges.insertNext(nullptr, &vertex);
    return true;
}

bool GraphVertex::removeEdge(GraphVertex& vertex)
{
    ListElement* prev = nullptr;
    ListElement* le = edges.getHead();
    while (le) {
        if (&vertex == le->data) {
            edges.removeNext(prev);
            return true;
        }
        prev = le;
        le = edges.getNext(le);
    }
    return false;
}

bool GraphVertex::isEdge(const GraphVertex& vertex)
{
    ListElement* le = edges.getHead();
    while (le && le->data) {
        if (&vertex == le->data)
            return true;
        le = le->next;
    }
    return false;
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
        destroyWithCallback();
    else
        destroyWithoutCallback();

    match = nullptr;
    destroyFunc = nullptr;
    edgesCount = 0;
}

bool Graph::insertVertexByData(void* data)
{
    if (!data || !match || getVertexByData(data))
        return false;

    vertexList.insertNext(nullptr, new GraphVertex(data));
    return true;
}

bool Graph::removeVertex(GraphVertex& vertex)
{
    ListElement* prev = nullptr;
    ListElement* le = vertexList.getHead();
    while (le) {
        if (&vertex == le->data) {
            deleteVertex(*(GraphVertex*)vertexList.removeNext(prev));
            return true;
        }
        prev = le;
        le = le->next;
    }
    return false;
}

bool Graph::insertEdge(GraphVertex& fromVertex, GraphVertex& toVertex)
{
    if (!isVertex(fromVertex) || !isVertex(toVertex) || fromVertex.isEdge(toVertex))
        return false;

    edgesCount++;
    fromVertex.insertEdge(toVertex);
    return true;
}

bool Graph::removeEdge(GraphVertex& fromVertex, GraphVertex& toVertex)
{
    if (!isVertex(fromVertex) || !isVertex(toVertex))
        return false;

    if (fromVertex.removeEdge(toVertex)) {
        edgesCount--;
        return true;
    }
    return false;
}

GraphVertex* Graph::getVertexByData(const void* data)
{
    if (!data || !match)
        return nullptr;

    ListElement* le = vertexList.getHead();
    while (le && le->data) {
        if (match(data, ((GraphVertex*)le->data)->data))
            return (GraphVertex*)le->data;
        le = le->next;
    }

    return nullptr;
}

void Graph::deleteVertex(GraphVertex& vertex)
{
    edgesCount -= vertex.getEdges().getSize();
    vertex.data = nullptr;
    delete &vertex;
}

bool Graph::isVertex(GraphVertex& vertex)
{
    ListElement* le = vertexList.getHead();
    while (le) {
        if (&vertex == le->data)
            return true;
        le = le->next;
    }
    return false;
}

void Graph::destroyWithCallback(void)
{
    while (vertexList.getSize()) {
        GraphVertex* vertex = (GraphVertex*)vertexList.removeNext(nullptr);
        destroyFunc(vertex->getData());
        delete vertex;
    }
}

void Graph::destroyWithoutCallback(void)
{
    while (vertexList.getSize())
        delete (GraphVertex*)vertexList.removeNext(nullptr);
}