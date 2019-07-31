#include "../include/graph.hpp"

bool GraphVertex::insertEdge(void* data)
{
    if (!data && edges.getElementByData(data))
        return false;
    edges.insertNext(nullptr, data);
    return true;
}

bool GraphVertex::removeEdge(void* data)
{
    return data && edges.removeElementByData(data);
}

void Graph::setMatch(match_t match)
{
    this->match = match;
    vertexList.forEach([](void* vertex, void *that) {
        if (vertex)
            (*(GraphVertex*)vertex).match = ((Graph*)that)->match;
    }, this);
}