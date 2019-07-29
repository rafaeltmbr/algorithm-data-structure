#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(const void* data1, const void* data2);

class GraphVertex {
protected:
    void* data;
    List edges;

public:
    match_t match;
    GraphVertex(void* data, match_t match = nullptr);
    GraphVertex(GraphVertex& graphVertex);
    ~GraphVertex(void) { data = nullptr; }
    bool insertEdge(void* data);
    void* removeEdge(void* data);
    int getEdgesCount(void) { return edges.getSize(); }
    List getEdges(void) { return edges; }
    void* getData(void) { return data; }
    void* getEdge(void* data);
};

class Graph {
protected:
    int edgesCount = 0;
    List vertexList;

public:
    match_t match;
    destroy_t destroyFunc;
    Graph(match_t match = nullptr, destroy_t destroyFunc = nullptr);
    Graph(Graph& graph);
    ~Graph(void);
    void destroy(void);
    bool insertVertex(void* data);
    void* removeVertex(void* data);
    bool insertEdge(void* fromVertexData, void* toVertexData);
    bool removeEdge(void* fromVertexData, void* toVertexData);
    const List& getAdjacencyList(const void* data);
    const List& getVertexList(void) { return vertexList; }
    bool isAdjacent(const void* vertex, const void* adjacentVertex);
    bool isVertex(const void* vertex);
};

#endif // GRAPH_HPP