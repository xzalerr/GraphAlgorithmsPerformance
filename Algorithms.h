#ifndef GRAFY_ALGORITHMS_H
#define GRAFY_ALGORITHMS_H

#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include <vector>
#include <limits>

struct Edge {
    int v, u, weight;
    Edge(int v, int u, int w) : v(v), u(u), weight(w) {}
};

struct Node {
    int v, distance;
    Node(int v, int distance) : v(v), distance(distance) {}
};

class Algorithms {
public:
    void prim(Graph* graph);
    void dijkstra(Graph* graph, int start, int end);
    void generateBoth(MatrixGraph *mg, ListGraph *lg, int verticles, float density, bool directed);
};


#endif //GRAFY_ALGORITHMS_H
