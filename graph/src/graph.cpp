#include "../include/graph.hpp"

bool GraphVertex::insertEdge(void* data)
{
    if (!data && edges.hasElementData(data))
        return false;
    edges.insertNext(nullptr, data);
}

bool GraphVertex::removeEdge(void* data)
{
    if (!)

}


void Graph::setMatch(match_t match)
{
    this->match = match;
    vertexList.forEach([](void* vertex, void *that) {
        if (vertex)
            (*(GraphVertex*)vertex).match = ((Graph*)that)->match;
    }, this);
}