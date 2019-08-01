#include "../include/graph.hpp"

bool GraphVertex::insertEdge(void* data)
{
    if (!data || edges.getElementByData(data))
        return false;
    edges.insertNext(nullptr, data);
    return true;
}

bool GraphVertex::removeEdge(void* data)
{
    return data && edges.removeElementByData(data);
}

GraphVertex* Graph::getVertexByData(const void* data)
{
    if (!data)
        return nullptr;

    static match_t m;
    m = match;

    static const void* d;
    d = data;

    static List* list;
    list = &vertexList;

    static GraphVertex* v;

    vertexList.forEach([](void* vertex) {
        if (!vertex)
            return;

        v = (GraphVertex*)vertex;
        if (m ? m(d, v->data) : d == v->data)
            list->forEachEnabled = false;
    });
    return list->forEachEnabled == false ? v : nullptr;
}

Graph::Graph()
{
    static match_t* m = &match;
    vertexList.match = [](const void* data1, const void* data2) {
        if (!data1 || !data2)
            return false;

        GraphVertex& vertex = *(GraphVertex*)data2;
        return *m ? (*m)(data1, vertex.data) : data1 == vertex.data;
    };
}

Graph::Graph(Graph& graph)
{
    match = graph.match;
    destroyFunc = graph.destroyFunc;

    static List& v = vertexList;
    graph.vertexList.forEach([](void* vertex) {
        GraphVertex* newVertex = new GraphVertex(((GraphVertex*)vertex)->data);
        newVertex->edges.insertNext(nullptr, ((GraphVertex*)vertex)->edges);
        v.insertNext(nullptr, newVertex);
    });
}

Graph::~Graph(void)
{
    destroy();
    match = nullptr;
    destroyFunc = nullptr;
}

void Graph::destroy(void)
{
    vertexList.setDestroy(destroyFunc);
    vertexList.destroy();
}

void Graph::setMatch(match_t match)
{
    this->match = match;
    static match_t m = match;
    vertexList.forEach([](void* vertex) {
        if (vertex)
            (*(GraphVertex*)vertex).edges.match = m;
    });
}

bool Graph::insertVertex(void* vertexData)
{
    if (!vertexData || getVertexByData(vertexData))
        return false;

    vertexList.insertNext(nullptr, new GraphVertex(vertexData));
    return true;
}

bool Graph::removeVertex(void* vertexData)
{
    if (!vertexData)
        return false;

    bool removeFlag = false;
    GraphVertex* vertex = getVertexByData(vertexData);
    if (vertex) {
        removeFlag = vertexList.removeElementByData(vertex->data);
        delete vertex;
    }
    return removeFlag;
}

bool Graph::insertEdge(void* fromVertexData, void* toVertexData)
{
    GraphVertex* vertex = getVertexByData(fromVertexData);
    if (!vertex || !getVertexByData(toVertexData))
        return false;

    return vertex->insertEdge(toVertexData);
}

bool Graph::removeEdge(void* fromVertexData, void* toVertexData)
{
    GraphVertex* vertex = getVertexByData(fromVertexData);
    if (!vertex)
        return false;

    return vertex->removeEdge(toVertexData);
}

List* Graph::getAdjacencyList(void* vertexData)
{
    GraphVertex* vertex = getVertexByData(vertexData);
    return vertex ? &vertex->edges : nullptr;
}

bool Graph::hasVertex(void* vertexData)
{
    return getVertexByData(vertexData);
}

int Graph::howManyEdges(void)
{
    static int acc;
    acc = 0;
    vertexList.forEach([](void* vertex) {
        acc += ((GraphVertex*)vertex)->edges.getSize();
    });
    return acc;
}
