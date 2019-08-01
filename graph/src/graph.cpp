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

Graph::Graph()
{
    static match_t *m = &match;
    vertexList.match = [](const void *data1, const void *data2)
    {
        if (!data1 || !data2)
            return false;

        GraphVertex &vertex = *(GraphVertex*) data2;
        return *m ? (*m)(data1, vertex.data) : data1 == vertex.data;
    };
}

Graph::Graph(Graph& graph)
{
    match = graph.match;
    destroyFunc = graph.destroyFunc;

    static List& v = vertexList;
    graph.vertexList.forEach([](void *vertex) {
        GraphVertex *newVertex = new GraphVertex(((GraphVertex*)vertex)->data);
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
    if (!vertexData || vertexList.getElementByData(vertexData))
        return false;

    vertexList.insertNext(nullptr, new GraphVertex(vertexData));
    return true;
}

bool Graph::removeVertex(void* vertexData)
{
    if (!vertexData)
        return false;

    delete (GraphVertex*) vertexList.removeElementByData(vertexData);
    return true;
}

bool Graph::insertEdge(void* fromVertexData, void* toVertexData)
{
    if (!fromVertexData || !toVertexData)
        return false;

    ListElement *le = vertexList.getElementByData(fromVertexData);
    if (!le || !le->data || !vertexList.getElementByData(toVertexData))
        return false;

    GraphVertex &vertex = *(GraphVertex*)le->data;
    return vertex.insertEdge(toVertexData);
}

bool Graph::removeEdge(void* fromVertexData, void* toVertexData)
{
    if (!fromVertexData || !toVertexData)
        return false;

    ListElement *le = vertexList.getElementByData(fromVertexData);
    if (!le || !le->data)
        return false;

    GraphVertex& vertex = *(GraphVertex*)le->data;
    return vertex.removeEdge(toVertexData);
}

List* Graph::getAdjacencyList(void* vertexData)
{
    if (!vertexData)
        return nullptr;

    ListElement* le = vertexList.getElementByData(vertexData);
    if (!le || !le->data)
        return nullptr;

    GraphVertex *vertex = ((GraphVertex*)le->data);
    return &vertex->edges;
}

bool Graph::hasVertex(void* vertexData)
{
    return vertexData && vertexList.getElementByData(vertexData);
}

int Graph::howManyEdges(void)
{
    static int acc = 0;
    vertexList.forEach([](void *vertex) {
        acc += ((GraphVertex*)vertex)->edges.getSize();
    });
    return acc;
}
