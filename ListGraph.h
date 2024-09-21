#ifndef GRAFY_LISTGRAPH_H
#define GRAFY_LISTGRAPH_H

#include "Graph.h"
#include <vector>
#include <list>

class ListGraph : public Graph {
public:
    std::list<std::pair<int, int>> *list;

    ListGraph();

    void initialize() override;
    void addEdge(int v, int u, int weight) override;
    void removeEdge(int v, int u) override;
    bool isPresent(int v, int u) override;
    void display() override;

    ~ListGraph() override;
};


#endif //GRAFY_LISTGRAPH_H
