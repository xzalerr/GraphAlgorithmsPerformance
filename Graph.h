#ifndef GRAFY_GRAPH_H
#define GRAFY_GRAPH_H

#include <iostream>
#include <list>

class Graph {
public:
    int v;
    int e;
    bool directed;
    int eCount = 0;
    int** matrix;
    std::list<std::pair<int, int>> *list;

    Graph() : v(0), e(0), directed(false){}

    virtual void initialize() = 0;
    virtual void addEdge(int v, int u, int weight) = 0;
    virtual void removeEdge(int v, int u) = 0;
    virtual bool isPresent(int v, int u) = 0;
    virtual void display() = 0;
    void load(std::string, bool directed);
    void generate(int verticles, float density, bool directed);

    virtual ~Graph() = default;
};


#endif //GRAFY_GRAPH_H
