#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(const void* data1, const void* data2);

class GraphVertex {
public:
    match_t match = nullptr;
    void* data = nullptr;
    List edges;
    
    GraphVertex() {};
    GraphVertex(void* data) { this->data = data; }
    ~GraphVertex(void) { data = nullptr; }
    bool insertEdge(void* data);
    bool removeEdge(void* data);
    bool hasEdge(const void* data);
};

class Graph {
public:
    List vertexList;
    match_t match;
    destroy_t destroyFunc;

    Graph(){};
    Graph(Graph& graph);
    ~Graph(void);
    void destroy(void);
    bool insertVertex(void* vertexData);
    bool removeVertex(void* vertexData);
    bool insertEdge(void* fromVertexData, void* toVertexData);
    bool removeEdge(void* fromVertexData, void* toVertexData);
    List* getAdjacencyList(void *vertexData);
    bool hasVertex(void* data);
    int howManyVertexes(void) { return vertexList.getSize(); }
    int howManyEdges(void);
};

#endif // GRAPH_HPP