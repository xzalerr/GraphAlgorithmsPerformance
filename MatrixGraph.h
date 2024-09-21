#ifndef GRAFY_MATRIXGRAPH_H
#define GRAFY_MATRIXGRAPH_H

#include "Graph.h"
#include <vector>

class MatrixGraph : public Graph {
public:
    int** matrix;

    MatrixGraph();

    void initialize() override;
    void addEdge(int v, int u, int weight) override;
    void removeEdge(int v, int u) override;
    bool isPresent(int v, int u) override;
    void display() override;

    ~MatrixGraph() override;
};


#endif //GRAFY_MATRIXGRAPH_H
