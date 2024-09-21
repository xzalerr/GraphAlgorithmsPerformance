#ifndef GRAFY_MENU_H
#define GRAFY_MENU_H

#include <iostream>

class Menu {
public:
    void menu();
    void simulate();
    void saveDurationToFile(const std::string& filename, double duration);
};


#endif //GRAFY_MENU_H
