/* Build Commands:
    g++ graph-testbench.cpp ../src/graph.cpp ../../list/src/list.cpp -g -Wall -std=c++14 -o graph.exe
*/

#include "../include/graph.hpp"
#include <iostream>

#define ASSERT(cond, msg)                                                         \
    if (cond)                                                                     \
        std::cout << "#";                                                         \
    else {                                                                        \
        std::cerr << "\n Test failed (" << __LINE__ << "): " << msg << std::endl; \
        exit(EXIT_FAILURE);                                                       \
    }

using namespace std;

void testConstructor(Graph& graph);
void testInsertVertex(Graph& graph);
void testRemoveVertex(Graph& graph);
void testInsertEdges(Graph& graph);
void testRemoveEdges(Graph& graph);
void testNoMatchFunction(Graph& graph);
void testGetMethods(Graph& graph);
void testDestroy(Graph& graph);

int main()
{
    cout << "------------------------ Graph Testbench ------------------------\n";
    Graph graph;
    testConstructor(graph);
    testInsertVertex(graph);
    testRemoveVertex(graph);
    testInsertEdges(graph);
    testRemoveEdges(graph);
    testNoMatchFunction(graph);
    testGetMethods(graph);
    testDestroy(graph);
    cout << "------------------------ Testbench Succeed ------------------------" << endl;
}

void testConstructor(Graph& graph)
{
    cout << " Constructor Test: ";

    const int charArraySize = 3;
    char charArray[charArraySize] = { 'A', 'B', 'C' };

    graph.match = [](const void* char1, const void* char2) {
        if (!char1 || !char2)
            return false;

        char c1 = *(char*)char1;
        char c2 = *(char*)char2;
        return c1 == c2;
    };

    ASSERT(graph.howManyVertexes() == 0, "graph shouldn't have vertexes");
    ASSERT(graph.howManyEdges() == 0, "Graph shouldn't have edges");

    for (int i = 0; i < charArraySize; i++)
        ASSERT(graph.insertVertex(charArray + i), "insertVertex() failed on loop: " << i);
    ASSERT(graph.insertEdge(charArray, charArray + 2), "insertEdge() failed");
    ASSERT(graph.howManyVertexes() == 3, "howManyVertexes() failed");
    ASSERT(graph.howManyEdges() == 1, "howManyEdges() failed");

    Graph copy(graph);
    ASSERT(copy.howManyVertexes() == 3, "howManyVertexes() failed");
    ASSERT(copy.howManyEdges() == 1, "howManyEdges() failed");

    ASSERT(graph.hasVertex(charArray), "hasVertex() failed");
    ASSERT(graph.removeVertex(charArray), "remove() failed");
    ASSERT(!graph.hasVertex(charArray), "hasVertex() failed");
    ASSERT(graph.howManyVertexes() == 2, "howManyVertexes() failed");

    for (int i = 1; i < charArraySize; i++)
        ASSERT(graph.removeVertex(charArray + i), "removeVertex() failed on loop: " << i);
    ASSERT(graph.howManyVertexes() == 0, "graph shouldn't have vertexes");
    ASSERT(graph.howManyEdges() == 0, "Graph shouldn't have edges");
    ASSERT(copy.howManyVertexes() == 3, "howManyVertexes() failed");
    ASSERT(copy.howManyEdges() == 1, "howManyEdges() failed");

    cout << " PASSED\n";
}

void testInsertVertex(Graph& graph)
{
    cout << " Insert Vertex Test: ";

    const int arraySize = 10;
    int iarray[arraySize] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    graph.match = [](const void* data1, const void* data2) {
        if (!data1 || !data2)
            return false;

        int d1 = *(int*)data1;
        int d2 = *(int*)data2;
        return d1 == d2;
    };

    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(!graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    graph.destroy();
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");

    cout << " PASSED\n";
}

void testRemoveVertex(Graph& graph)
{
    cout << " Remove Vertex Test: ";

    const int arraySize = 10;
    int iarray[arraySize] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int narray[arraySize] = { -10, -20, -30, -40, -50, -60, -70, -80, -90, -100 };

    graph.match = [](const void* data1, const void* data2) {
        if (!data1 || !data2)
            return false;

        int d1 = *(int*)data1;
        int d2 = *(int*)data2;
        return d1 == d2;
    };

    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(!graph.removeVertex(narray + i), "removeVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.removeVertex(iarray + i), "removeVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    cout << " PASSED\n";
}

void testInsertEdges(Graph& graph)
{
    cout << " Insert Edge Test: ";

    const int arraySize = 10;
    int iarray[arraySize] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int narray[arraySize] = { -10, -20, -30, -40, -50, -60, -70, -80, -90, -100 };

    graph.match = [](const void* data1, const void* data2) {
        if (!data1 || !data2)
            return false;

        int d1 = *(int*)data1;
        int d2 = *(int*)data2;
        return d1 == d2;
    };

    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    ASSERT(!graph.insertEdge(iarray, iarray), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 1; i < arraySize; i++)
        ASSERT(graph.insertEdge(iarray, iarray + i), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize - 1, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 1; i < arraySize; i++)
        ASSERT(!graph.insertEdge(iarray, iarray + i), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize - 1, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(!graph.insertEdge(iarray, narray + i), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize - 1, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    graph.destroy();
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    cout << " PASSED\n";
}

void testRemoveEdges(Graph& graph)
{
    cout << " Remove Edge Test: ";

    const int arraySize = 10;
    int iarray[arraySize] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int narray[arraySize] = { -10, -20, -30, -40, -50, -60, -70, -80, -90, -100 };

    graph.match = [](const void* data1, const void* data2) {
        if (!data1 || !data2)
            return false;

        int d1 = *(int*)data1;
        int d2 = *(int*)data2;
        return d1 == d2;
    };

    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 1; i < arraySize; i++)
        ASSERT(graph.insertEdge(iarray, iarray + i), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize - 1, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    ASSERT(graph.insertEdge(iarray + 1, iarray + 2), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    ASSERT(graph.removeVertex(iarray + 1), "removeVertex() failed");
    ASSERT(graph.howManyEdges() == arraySize - 2, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize - 1, "howManyVertexes() failed");

    for (int i = 2; i < arraySize; i++)
        ASSERT(!graph.removeEdge(iarray, narray + i), "removeEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize - 2, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize - 1, "howManyVertexes() failed");

    for (int i = 2; i < arraySize; i++)
        ASSERT(graph.removeEdge(iarray, iarray + i), "removeEdge() failed");
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize - 1, "howManyVertexes() failed");

    graph.destroy();
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    cout << " PASSED\n";
}

void testNoMatchFunction(Graph& graph)
{
    cout << " No Match Function Test: ";

    const int arraySize = 10;
    int iarray[arraySize] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int narray[arraySize] = { -10, -20, -30, -40, -50, -60, -70, -80, -90, -100 };

    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int i = 1; i < arraySize; i++)
        ASSERT(graph.insertEdge(iarray, iarray + i), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize - 1, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    ASSERT(graph.insertEdge(iarray + 1, iarray + 2), "insertEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    ASSERT(graph.removeVertex(iarray + 1), "removeVertex() failed");
    ASSERT(graph.howManyEdges() == arraySize - 2, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize - 1, "howManyVertexes() failed");

    for (int i = 2; i < arraySize; i++)
        ASSERT(!graph.removeEdge(iarray, narray + i), "removeEdge() failed");
    ASSERT(graph.howManyEdges() == arraySize - 2, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize - 1, "howManyVertexes() failed");

    for (int i = 2; i < arraySize; i++)
        ASSERT(graph.removeEdge(iarray, iarray + i), "removeEdge() failed");
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize - 1, "howManyVertexes() failed");

    graph.destroy();
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    cout << " PASSED\n";
}

int summation(int n)
{
    int acc = 0;
    for (; n; n--)
        acc += n;
    return acc;
}

void testGetMethods(Graph& graph)
{
    cout << " Get Methods Test: ";

    const int arraySize = 10;
    int iarray[arraySize] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    for (int j = 0; j < arraySize - 1; j++)
        for (int i = j + 1; i < arraySize; i++)
            ASSERT(graph.insertEdge(iarray + j, iarray + i), "insertVertex() failed in loop: " << j << ", " << i);
    ASSERT(graph.howManyEdges() == summation(arraySize - 1), "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    List list;

    ASSERT(graph.getVertexesList(&list), "getVertexesList() failed");
    ASSERT(list.getSize() == arraySize, "getSize() failed");
    for (int i = 0; i < arraySize; i++)
        ASSERT(list.getElementByData(iarray + i), "getElementByData() failed");
    list.destroy();

    for (int i = 0; i < arraySize; i++) {
        ASSERT(graph.getAdjacencyList(iarray + i, &list), "getAdjacencyList() failed");
        ASSERT(list.getSize() == arraySize - i - 1, "getSize() failed in loop: " << i);
        for (int j=i+1; j < arraySize; j++)
            ASSERT(list.getElementByData(iarray+j), "getElementByData() failed in loop: " << i << ", " << j);
        list.destroy();
    }

    graph.destroy();
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    cout << " PASSED\n";
}

void testDestroy(Graph& graph)
{
    cout << " Constructor Test: ";

    const int arraySize = 10;
    int iarray[arraySize] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");

    for (int i = 0; i < arraySize; i++)
        ASSERT(graph.insertVertex(iarray + i), "insertVertex() failed in loop: " << i);
    ASSERT(graph.howManyEdges() == 0, "howManyEdges() failed");
    ASSERT(graph.howManyVertexes() == arraySize, "howManyVertexes() failed");

    static int sum = 0;

    graph.destroyFunc = [](void* data) {
        int* d = (int*)data;
        sum += *d;
    };

    ASSERT(sum == 0, "sum should be 0");
    graph.destroy();
    ASSERT(graph.howManyVertexes() == 0, "howManyVertexes() failed");
    ASSERT(sum == summation(arraySize), "destroy() failed");

    cout << " PASSED\n";
}