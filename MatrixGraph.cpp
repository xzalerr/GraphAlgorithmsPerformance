#include <iostream>
#include <fstream>
#include <__random/random_device.h>
#include "MatrixGraph.h"

//konstruktor domyslny ustawiajacy licze wierzcholkow i krawedzi na 0, graf jest domyslnie nieskierowany
//macierz jest poczatkowo pust, a licznik krawedzi rowny 0
MatrixGraph::MatrixGraph() {
    this->v = 0;
    this->e = 0;
    this->directed = false;
    this->matrix = nullptr;
    this->eCount = 0;
}

//metoda do inicjalizacji grafu, jesli graf juz istnieje, poczatkowo czysczona jest jego zawartosc
//poprzez usuniecie tablic, a nastepnie tworzona jest nowa macierz o wymiarach v x e, licznik krawedzi rowny jest 0
void MatrixGraph::initialize() {
    delete[] matrix;
    this->eCount = 0;
    matrix = new int* [v];
    for (int i = 0; i < v; i++) {
        matrix[i] = new int[e]();
    }
}

//metoda dodajaca krawedz do grafu, zwieksza rozniez eCount, ktory wyznacza kolumne, do ktorej dodajemy wartosci
//w macierzy incydencji kazda kolumna odpowiada nowej krawedzi
//wierzcholek poczatkowy krawedzi jest dodatni i o wartosci wagi
//wierzcholek koncowy krawedzi jest ujemny i o wartosci wagi dla grafow skierowanych, dla nieskierowanych
//jest oznaczony tak samo jak poczatkowy
void MatrixGraph::addEdge(int v, int u, int weight) {
    if(directed) {
        matrix[v][eCount] = 1 * weight;
        matrix[u][eCount] = -1 * weight;
    } else {
        matrix[v][eCount] = 1 * weight;
        matrix[u][eCount] = 1 * weight;
    }
    eCount++;
}

//metoda umozliwajaca usuwanie krawedzi
void MatrixGraph::removeEdge(int v, int u) {
    bool deleted;
    for(int i = 0; i < e; i++) {
        if(matrix[v][i] != 0 && matrix[u][i] != 0 && matrix[v][i] > 0) {
            matrix[v][i] = 0;
            matrix[u][i] = 0;
            deleted = true;
            break;
        }
    }
    if(!deleted) std::cerr << "No such line to delete.\n";
}

//metoda sprawdzajaca czy dana krawedz zaczynajaca sie w v i konczaca w u istnieje w grafie
bool MatrixGraph::isPresent(int v, int u) {
    for(int i = 0; i < e; i++) {
        if(matrix[v][i] != 0 && matrix[u][i] != 0 && matrix[v][i] > 0) return true;
    }
    return false;
}

//wyswietlanie grafu zaprezentowanego za pomoca macierzy incydencji
void MatrixGraph::display() {
    std::cout << "Matrix: \n";
    std::cout<<"  ";
    for(int i = 0; i < e; i++) std::cout << std::setw(4) << i << " ";
    std::cout<<std::endl;
    for(int i = 0; i < v; i++) {
        std::cout<<i<<" ";
        for(int j = 0; j < e; j++) {
            std::cout << std::setw(4) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

//dekonstruktor grafu, usuwa tablice matrix jesli nie jest pusta
MatrixGraph::~MatrixGraph() {
    if (matrix != nullptr) {
        for (int i = 0; i < v; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}
