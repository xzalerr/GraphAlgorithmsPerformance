#include "Menu.h"
#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Algorithms.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <utility>
#include <random>

using namespace std;

//proste menu umozliwiajace wykonywanie zadanych w poleceniu opcji w zaleznosci od wyboru uzytkownika
void Menu::menu() {
    MatrixGraph mg;
    ListGraph lg;
    Algorithms a;
    int problem = 0;
    while (problem != -1) {
        cout << "Wybierz problem:\n";
        cout << "1. Minimalne drzewo rozpinające.\n2. Najkrótsza ścieżka w grafie.\n-1. Zakończ program.\n";
        cin >> problem;
        if (problem == 1) {
            int mst = 0;
            while (true) {
                cout << "1. Wczytaj dane z pliku.\n";
                cout << "2. Wygeneruj graf losowo.\n";
                cout << "3. Wyświetl graf listowo i macierzowo na ekranie.\n";
                cout << "4. Algorytm Prima macierzowo i listowo z wyświetleniem wyników.\n";
                cout << "-1. Zmień problem.\n";
                cin >> mst;
                if (mst == 1) {
                    string name;
                    cout << "Podaj nazwę pliku: \n";
                    cin >> name;
                    lg.load(name, false);
                    mg.load(name, false);
                    cout << "Pomyślnie wczytano.\n";
                } else if (mst == 2) {
                    int v;
                    float d;
                    cout << "Podaj liczbe wierzchołków i gęstość, oddzielone spacją: ";
                    cin >> v >> d;
                    cout << "Liczba wierzchołków: " << v << ", Gęstość: " << d << endl; // Debugowanie
                    a.generateBoth(&mg, &lg, v, d, false);
                    cout << "Wygenerowano pomyślnie.\n";
                } else if (mst == 3) {
                    lg.display();
                    mg.display();
                } else if (mst == 4) {
                    auto start = std::chrono::high_resolution_clock::now();
                    a.prim(&lg);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::cout << "Czas trwania algorytmu Prima lista: " << duration.count() << " sekund" << std::endl;

                    start = std::chrono::high_resolution_clock::now();
                    a.prim(&mg);
                    end = std::chrono::high_resolution_clock::now();
                    duration = end - start;
                    std::cout << "Czas trwania algorytmu Prima macierz: " << duration.count() << " sekund" << std::endl;
                } else if (mst == -1) {
                    problem = 0;
                    break;
                } else {
                    cout << "Nie ma takiej opcji.\n";
                }
            }
        } else if (problem == 2) {
            int fsp = 0;
            while (true) {
                cout << "1. Wczytaj dane z pliku.\n";
                cout << "2. Wygeneruj graf losowo.\n";
                cout << "3. Wyświetl graf listowo i macierzowo na ekranie.\n";
                cout << "4. Algorytm Dijkstry macierzowo i listowo z wyświetleniem wyników.\n";
                cout << "-1. Zmień problem.\n";
                cin >> fsp;
                if (fsp == 1) {
                    string name;
                    cout << "Podaj nazwę pliku: \n";
                    cin >> name;
                    lg.load(name, true);
                    mg.load(name, true);
                    cout << "Pomyślnie wczytano.\n";
                } else if (fsp == 2) {
                    int v;
                    float d;
                    cout << "Podaj liczbe wierzchołków i gęstość, oddzielone spacją: ";
                    cin >> v >> d;
                    cout << "Liczba wierzchołków: " << v << ", Gęstość: " << d << endl;
                    a.generateBoth(&mg, &lg, v, d, true);
                    cout << "Wygenerowano pomyślnie.\n";
                } else if (fsp == 3) {
                    lg.display();
                    mg.display();
                } else if (fsp == 4) {
                    int s, e;
                    cout << "Podaj liczbe wierzchołek startowy i końcowy, oddzielone spacją: ";
                    cin >> s >> e;

                    auto start = std::chrono::high_resolution_clock::now();
                    a.dijkstra(&lg, s, e);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::cout << "Czas trwania algorytmu Dijkstry lista: " << duration.count() << " sekund" << std::endl;

                    start = std::chrono::high_resolution_clock::now();
                    a.dijkstra(&mg, s, e);
                    end = std::chrono::high_resolution_clock::now();
                    duration = end - start;
                    std::cout << "Czas trwania algorytmu Dijkstry macierz: " << duration.count() << " sekund" << std::endl;
                } else if (fsp == -1) {
                    problem = 0;
                    break;
                } else {
                    cout << "Nie ma takiej opcji.\n";
                }
            }
        } else if (problem == -1) {
            cout << "Koniec.\n";
            break;
        } else {
            cout << "Nie ma takiej opcji.\n";
        }
    }
}

//funkcja sluzaca do wykonywania pomiarow czasowych algorytmow prima i dijkstry dla grafow o gestosciac 0.25; 0.5; 0.99
//pomiary wykonywane sa dla rozmiarow zadanych w length
void Menu::simulate() {
    std::vector<int> lengths = {65, 130, 190, 250, 310, 370, 430};
    MatrixGraph mg;
    ListGraph lg;
    Algorithms a;
    //wykonujemy po 50 pomiarow dla kazdej ilosci wierzcholkow i gestosci dla algorytmu prima
    for(int length : lengths) {
        for(int i = 0; i < 50; i++) {
            a.generateBoth(&mg, &lg, length, 0.25, false);

            auto start = std::chrono::high_resolution_clock::now();
            a.prim(&mg);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            saveDurationToFile("Prim_Matrix_" + std::to_string(length) + "_025.txt", duration.count());


            start = std::chrono::high_resolution_clock::now();
            a.prim(&lg);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Prim_List_" + std::to_string(length) + "_025.txt", duration.count());

            a.generateBoth(&mg, &lg, length, 0.5, false);

            start = std::chrono::high_resolution_clock::now();
            a.prim(&mg);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Prim_Matrix_" + std::to_string(length) + "_05.txt", duration.count());

            start = std::chrono::high_resolution_clock::now();
            a.prim(&lg);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Prim_List_" + std::to_string(length) + "_05.txt", duration.count());

            a.generateBoth(&mg, &lg, length, 0.99, false);

            start = std::chrono::high_resolution_clock::now();
            a.prim(&mg);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Prim_Matrix_" + std::to_string(length) + "_099.txt", duration.count());

            start = std::chrono::high_resolution_clock::now();
            a.prim(&lg);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Prim_List_" + std::to_string(length) + "_099.txt", duration.count());
        }
    }


    //wykonujemy po 50 pomiarow dla kazdej ilosci wierzcholkow i gestosci dla algorytmu dijkstry
    for(int length : lengths) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> final(0, length - 1);
        for(int i = 0; i < 50; i++) {
            int fin = final(gen);
            a.generateBoth(&mg, &lg, length, 0.25, true);

            auto start = std::chrono::high_resolution_clock::now();
            a.dijkstra(&mg, 0, fin);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            saveDurationToFile("Dijkstra_Matrix_" + std::to_string(length) + "_025.txt", duration.count());


            start = std::chrono::high_resolution_clock::now();
            a.dijkstra(&lg, 0, fin);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Dijkstra_List_" + std::to_string(length) + "_025.txt", duration.count());

            a.generateBoth(&mg, &lg, length, 0.5, true);

            start = std::chrono::high_resolution_clock::now();
            a.dijkstra(&mg, 0, fin);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Dijkstra_Matrix_" + std::to_string(length) + "_05.txt", duration.count());

            start = std::chrono::high_resolution_clock::now();
            a.dijkstra(&lg, 0, fin);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Dijkstra_List_" + std::to_string(length) + "_05.txt", duration.count());

            a.generateBoth(&mg, &lg, length, 0.99, true);

            start = std::chrono::high_resolution_clock::now();
            a.dijkstra(&mg, 0, fin);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Dijkstra_Matrix_" + std::to_string(length) + "_099.txt", duration.count());

            start = std::chrono::high_resolution_clock::now();
            a.dijkstra(&lg, 0, fin);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            saveDurationToFile("Dijkstra_List_" + std::to_string(length) + "_099.txt", duration.count());
        }
    }
}

void Menu::saveDurationToFile(const std::string& filename, double duration) {
    std::ofstream outFile(filename, std::ios_base::app);
    if (outFile.is_open()) {
        outFile << duration << "\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
