#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../../list/include/list.hpp"

typedef bool (*match_t)(const void* data1, const void* data2);

class GraphVertex {
protected:
    void* data;
    List edges;
    friend class Graph;

public:
    GraphVertex(void* data) { this->data = data; }
    GraphVertex(GraphVertex& vertex);
    ~GraphVertex(void) { data = nullptr; }
    bool insertEdge(GraphVertex* vertex);
    bool removeEdge(GraphVertex* vertex);
    const List& getEdges(void) { return edges; }
    void* getData(void) { return data; }
    bool hasEdge(const GraphVertex* vertex);
};

class Graph {
protected:
    int edgesCount = 0;
    List vertexList;
    void deleteVertex(GraphVertex& vertex);
    void destroyWithCallback(void);
    void destroyWithoutCallback(void);

public:
    match_t match;
    destroy_t destroyFunc;
    Graph(match_t match = nullptr, destroy_t destroyFunc = nullptr);
    Graph(Graph& graph);
    ~Graph(void);
    void destroy(void);
    bool insertVertexByData(void* data);
    bool removeVertex(GraphVertex& vertex);
    bool removeVertex(void* data);
    bool insertEdge(GraphVertex& fromVertex, GraphVertex& toVertex);
    bool insertEdge(void* fromVertexData, void* toVertexData);
    bool removeEdge(GraphVertex& fromVertex, GraphVertex& toVertex);
    bool removeEdge(void* fromVertexData, void* toVertexData);
    const List& getVertexList(void) const { return vertexList; }
    GraphVertex* getVertexByData(const void* data);
    bool isAdjacent(GraphVertex& fromVertex, GraphVertex& toVertex) { return fromVertex.hasEdge(&toVertex); }
    bool isAdjacent(void* fromVertexData, void* toVertexData);
    bool hasVertex(GraphVertex& vertex);
    bool hasVertex(void* data);
    int howManyVertexes(void) { return vertexList.getSize(); }
    int howManyEdges(void) { return edgesCount; }
};

#endif // GRAPH_HPP