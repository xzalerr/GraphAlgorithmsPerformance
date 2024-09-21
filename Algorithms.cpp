#include "Algorithms.h"
#include <iostream>
#include <queue>
#include <utility>
#include <random>
#include <set>

//algorytm prima dzialajacy zarowno na grafie reprezentpwanym macierzowo jak i listowo
//z kolejki priorytetowej krawedzie dodawane sa wg najmniejszych wag, jesli nie lacza bedacych
//juz w mst wierzcholkow
void Algorithms::prim(Graph* graph) {
    int verticles = graph->v;
    int edges = graph->e;
    std::vector<bool> visited(verticles, false);
    std::list<Edge> mst;
    int totalWeight = 0;

    auto ComparePrim = [](Edge e1, Edge e2) {
        return e1.weight > e2.weight;
    };
    std::priority_queue<Edge, std::vector<Edge>, decltype(ComparePrim)> pq(ComparePrim);

    int startVertex = 0;
    visited[startVertex] = true;

    if (auto* mg = dynamic_cast<MatrixGraph*>(graph)) {
        for (int e = 0; e < edges; e++) {
            if (mg->matrix[startVertex][e] != 0) {
                for (int u = 0; u < verticles; u++) {
                    if (u != startVertex && mg->matrix[u][e] != 0) {
                        pq.emplace(startVertex, u, mg->matrix[startVertex][e]);
                        break;
                    }
                }
            }
        }
    } else if (auto* lg = dynamic_cast<ListGraph*>(graph)) {
        for (const auto& it : lg->list[startVertex]) {
            pq.emplace(startVertex, it.first, it.second);
        }
    }

    while (!pq.empty() && mst.size() < verticles - 1) {
        Edge edge = pq.top();
        pq.pop();
        if(!visited[edge.u]) {
            visited[edge.u] = true;
            mst.push_back(edge);
            totalWeight += edge.weight;

            if (auto* mg = dynamic_cast<MatrixGraph*>(graph)) {
                for (int e = 0; e < edges; e++) {
                    if (mg->matrix[edge.u][e] != 0) {
                        for (int u = 0; u < verticles; u++) {
                            if (u != edge.u && mg->matrix[u][e] != 0) {
                                pq.emplace(edge.u, u, mg->matrix[edge.u][e]);
                                break;
                            }
                        }
                    }
                }
            } else if (auto* lg = dynamic_cast<ListGraph*>(graph)) {
                for (const auto& it : lg->list[edge.u]) {
                    pq.emplace(edge.u, it.first, it.second);
                }
            }
        }
    }

    std::cout << "Minimum Spanning Tree:" << std::endl;
    for (Edge e : mst) {
        std::cout << e.v << " - " << e.u << " : " << e.weight << std::endl;
    }
    std::cout << "Total weight: " << totalWeight << std::endl;
}

//algorytm dijkstry dzialajacy zarowno na grafie reprezentpwanym macierzowo jak i listowo
//wybieramy wierzcholek o najmniejszym koszcie dojscia i aktualizujemy
//koszty dojscia do sasiadow, jesli mozliwe jest zredukowanie kosztu dojscia
void Algorithms::dijkstra(Graph* graph, int start, int end) {
    int verticles = graph->v;
    int edges = graph->e;
    std::vector<int> distance(verticles, INT_MAX);
    std::vector<int> predecessor(verticles, -1);
    distance[start] = 0;

    auto CompareDijkstra = [](Node n1, Node n2) {
        return n1.distance > n2.distance;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(CompareDijkstra)> pq(CompareDijkstra);
    pq.emplace(start, 0);

    while(!pq.empty()) {
        int v = pq.top().v;
        pq.pop();

        if (auto* mg = dynamic_cast<MatrixGraph*>(graph)) {
            for (int e = 0; e < edges; e++) {
                if (mg->matrix[v][e] != 0) {
                    for (int u = 0; u < verticles; u++) {
                        if (u != v && mg->matrix[u][e] < 0) {
                            int w = abs(mg->matrix[u][e]);
                            if(distance[v]+w<distance[u]) {
                                distance[u] = distance[v] + w;
                                predecessor[u] = v;
                                pq.emplace(u, distance[u]);
                            }
                        }
                    }
                }
            }
        } else if (auto* lg = dynamic_cast<ListGraph*>(graph)) {
            for (const auto& [u, weight] : lg->list[v]) {
                if (distance[v] + weight < distance[u]) {
                    distance[u] = distance[v] + weight;
                    predecessor[u] = v;
                    pq.emplace(u, distance[u]);
                }
            }
        }
    }
    std::vector<int> path;
    for (int at = end; at != -1; at = predecessor[at])
        path.push_back(at);
    std::reverse(path.begin(), path.end());

    if (path.size() == 1 && path[0] != start) {
        std::cerr << "No path exists between the given vertices.\n";
        return;
    }

    std::cout << "Shortest path from " << start << " to " << end << ": ";
    for (int v : path)
        std::cout << v << " ";
    std::cout << "\nTotal cost: " << distance[end] << std::endl;
}

//funkcja generujaca jednoczesnie grafy macierzowy i listowy o zadanej gestosci i liczbie wierzcholkow
//poczatkowo graf generuje drzewo rozpinajace, sprawiajac ze graf jest spojny,
//dla skierowanych dodatkowo dodawane sa polaczenie pierwszego i ostatniego wierzcholka
//nastepnie wszystkie mozliwe krawedzie sa dodawane do wektora all, mieszane i w
//losowo wymieszanej kolejnosci dodawane sa do generowanego grafu, o ile nie sa juz dodane
void Algorithms::generateBoth(MatrixGraph *mg, ListGraph *lg, int verticles, float density, bool directed) {
    mg->v = verticles;
    mg->e = int(((verticles*(verticles-1)) / 2) * (directed ? 2 : 1) * density);
    mg->directed = directed;
    lg->v = verticles;
    lg->e = int(((verticles*(verticles-1)) / 2) * (directed ? 2 : 1) * density);
    lg->directed = directed;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, verticles - 1);
    std::uniform_int_distribution<int> weights(1, 1000);

    std::vector<int> vertIndexes(verticles);
    for (int i = 0; i < verticles; ++i) vertIndexes[i] = i;
    std::shuffle(vertIndexes.begin(), vertIndexes.end(), gen);
    mg->initialize();
    lg->initialize();

    for (int i = 0; i < verticles - 1; ++i) {
        int w = weights(gen);
        mg->addEdge(vertIndexes[i], vertIndexes[i + 1], w);
        lg->addEdge(vertIndexes[i], vertIndexes[i + 1], w);
    }

    if (directed) {
        int w = weights(gen);
        mg->addEdge(vertIndexes[verticles - 1], vertIndexes[0], w);
        lg->addEdge(vertIndexes[verticles - 1], vertIndexes[0], w);
    }

    std::vector<std::pair<int, int>> all;
    for (int i = 0; i < verticles; ++i) {
        for (int j = i + 1; j < verticles; ++j) {
            all.emplace_back(i, j);
            if (directed) all.emplace_back(j, i);
        }
    }

    std::shuffle(all.begin(), all.end(), gen);

    int more = lg->e - lg->eCount;
    for (int i = 0; i < more; ++i) {
        int v1 = all[i].first;
        int v2 = all[i].second;
        if (!lg->isPresent(v1, v2)) {
            int w = weights(gen);
            mg->addEdge(v1, v2, w);
            lg->addEdge(v1, v2, w);
        }
    }
}