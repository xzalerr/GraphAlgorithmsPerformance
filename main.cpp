#include <iostream>
#include "MatrixGraph.h"
#include "Menu.h"
int main() {
    Menu m;
    std::cout<<"Wybierz opcje:\n1. Menu\n2. Symulacja\n";
    int choice = 0;
    std::cin>>choice;
    if(choice==1) {
        m.menu();
    } else if(choice==2) {
        m.simulate();
    } else {
        std::cout<<"Nie ma takiej opcji!\n";
    }
    return 0;
}
