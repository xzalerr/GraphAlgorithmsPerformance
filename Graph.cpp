#include <iostream>
#include <fstream>
#include <__random/random_device.h>
#include <random>
#include "Graph.h"


//metoda umozliwiajaca wczytywanie grafow z pliku o zadanej nazwie oraz o okresleniu czy graf jest skierowany
//dane wcczytywane sa zgodnie ze schematem podanym w poleceniu projektu
void Graph::load(std::string filename, bool directed) {
    std::ifstream input(filename);
    if(!input.is_open()) {
        std::cerr << "Couldn't find given file!\n";
        return;
    }
    int verticles, edges;
    input >> edges >> verticles;
    this->v = verticles;
    this->e = edges;
    this->directed = directed;
    initialize();
    int s, e, w;
    while(input >> s >> e >> w) {
        addEdge(s, e, w);
    }
}

//funkcja generujaca graf o zadanej gestosci i liczbie wierzcholkow
//poczatkowo graf generuje drzewo rozpinajace, sprawiajac ze graf jest spojny,
//dla skierowanych dodatkowo dodawane sa polaczenie pierwszego i ostatniego wierzcholka
//nastepnie wszystkie mozliwe krawedzie sa dodawane do wektora all, mieszane i w
//losowo wymieszanej kolejnosci dodawane sa do generowanego grafu, o ile nie sa juz dodane
void Graph::generate(int verticles, float density, bool directed) {
    this->v = verticles;
    this->e = int(((verticles*(verticles-1)) / 2) * (directed ? 2 : 1) * density);
    this->directed = directed;
    std::cout << "Krawedzi: " << e << std::endl;
    std::vector<std::vector<bool>> visited(verticles, std::vector<bool>(verticles, false));


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, v-1);

    //tworzenie drzewa rozpinajacego, zapewniajac tym samym spojnosc grafu
    std::vector<int> vertIndexes(v);
    int w;
    for(int i = 0; i < v; i ++) vertIndexes[i] = i;
    std::shuffle(vertIndexes.begin(), vertIndexes.end(), std::default_random_engine(dist(gen)));
    initialize();
    for(int i = 0; i < v-1; i++) {
        w = (dist(gen))%10+1;
        addEdge(vertIndexes[i], vertIndexes[i+1], w);
        visited[vertIndexes[i]][vertIndexes[i+1]] = true;
    }
    if(directed) {
        addEdge(vertIndexes[v-1], vertIndexes[0], (dist(gen))%100+1);
        visited[vertIndexes[v-1]][vertIndexes[0]] = true;
    }

    //generowanie wszystkich mozliwych krawedzi przyspieszajac proces dodawania reszty krawedzi
    std::vector<std::pair<int, int>> all;
    for(int i = 0; i < v; i ++) {
        for(int j = i+1; j < v; j++) {
            all.emplace_back(i, j);
            if(directed) all.emplace_back(j, i);
        }
    }
    std::shuffle(all.begin(), all.end(), std::default_random_engine(dist(gen)));

    //dodawanie reszty krawedzi do grafu w zaleznosci od gestosci
    int more = e - eCount;
    for(int i = 0; i < more; i++) {
        if(!visited[all[i].first][all[i].second]) {
            w = (dist(gen))%100+1;
            addEdge(all[i].first, all[i].second, w);
            visited[vertIndexes[all[i].first]][all[i].second] = true;
        }
    }
}
