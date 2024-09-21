#include <iostream>
#include <__random/random_device.h>
#include "ListGraph.h"

//konstruktor domyslny ustawiajacy licze wierzcholkow i krawedzi na 0, graf jest domyslnie nieskierowany
//macierz jest poczatkowo pust, a licznik krawedzi rowny 0
ListGraph::ListGraph() {
    this->v = 0;
    this->e = 0;
    this->directed = false;
    this->list = nullptr;
    this->eCount = 0;
}

//metoda do inicjalizacji grafu, jesli graf juz istnieje, poczatkowo czysczona jest jego zawartosc
//poprzez usuniecie tablicy list a nastepnie tworzona jest nowa tablica list
void ListGraph::initialize() {
    delete[] list;
    this->eCount = 0;
    list = new std::list<std::pair<int, int>>[v];
}

//metoda dodajaca krawedz do grafu, zwieksza rozniez eCount, ktory wyznacza ilosc dodanych krawedzi
//indeks tablicy oznacza wierzcholek startowy, a w liscie sa wszystkie wierzcholki z nim polaczone
//dla skierowanego, v jest wierzcholkiem poczatkowym a wartosc w liscie koncowym
//w nieskierowanym v jest zarowno poczatkowym jak i koncowym
void ListGraph::addEdge(int v, int u, int weight) {
    list[v].emplace_back(u, weight);
    if(!directed) {
        list[u].emplace_back(v, weight);
    }
    eCount++;
}

//metoda umozliwajaca usuwanie krawedzi
void ListGraph::removeEdge(int v, int u) {
    for(auto i = list[v].begin(); i != list[v].end(); i++) {
        if(i->first==u) {
            list[v].erase(i);
            break;
        }
    }
    if(!directed) {
        for(auto i = list[u].begin(); i != list[u].end(); i++) {
            if(i->first==v) {
                list[u].erase(i);
                break;
            }
        }
    }
}

//metoda sprawdzajaca czy dana krawedz zaczynajaca sie w v i konczaca w u istnieje w grafie
bool ListGraph::isPresent(int v, int u) {
    for(auto i = list[v].begin(); i != list[v].end(); i++) {
        if(i->first==u) {
            return true;
        }
    }
    return false;
}

//wyswietlanie grafu zaprezentowanego za pomoca listy sasiedztwa
void ListGraph::display() {
    std::cout << "Adjacency List: \n";
    for(int i = 0; i < v; i++) {
        std::cout << i << " : ";
        for(auto j = list[i].begin(); j != list[i].end(); j++) {
            std::cout << "(" << j->first << "," << j->second << ") ";
        }
        std::cout << "\n";
    }
}

//dekonstruktor grafu, usuwa tablice list jesli nie jest pusta i czysci wszytskie przechowywane w niej listy
ListGraph::~ListGraph() {
    if(list!= nullptr) {
        for(int i = 0; i < v; i++) {
            list[i].clear();
        }
        delete[] list;
    }
}

