cmake_minimum_required(VERSION 3.27)
project(Grafy)

set(CMAKE_CXX_STANDARD 17)

add_executable(Grafy main.cpp
        Graph.h
        MatrixGraph.cpp
        MatrixGraph.h
        ListGraph.cpp
        ListGraph.h
        Graph.cpp
        Algorithms.cpp
        Algorithms.h
        Menu.cpp
        Menu.h
)
