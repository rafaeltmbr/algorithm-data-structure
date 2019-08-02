#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(const void* data1, const void* data2);

class GraphVertex {
protected:
    void* data = nullptr;
    List edges;
    friend class Graph;
    
public:
    GraphVertex();
    GraphVertex(void* data) { this->data = data; }
    ~GraphVertex(void) { data = nullptr; }
    bool insertEdge(void* data);
    bool removeEdge(void* data);
    bool hasEdge(const void* data) { return edges.getElementByData(data); }
};

class Graph {
protected:
    GraphVertex* getVertexByData(const void* data);
    List vertexList;

public:
    match_t match = nullptr;
    destroy_t destroyFunc = nullptr;

    Graph();
    Graph(Graph& graph);
    ~Graph(void);
    void destroy(void);
    bool insertVertex(void* vertexData);
    bool removeVertex(void* vertexData);
    bool insertEdge(void* fromVertexData, void* toVertexData);
    bool removeEdge(void* fromVertexData, void* toVertexData);
    bool getAdjacencyList(void* vertexData, List* list);
    bool getVertexesList(List* list);
    bool hasVertex(void* vertexData);
    int howManyVertexes(void) { return vertexList.getSize(); }
    int howManyEdges(void);
};

#endif // GRAPH_HPP
