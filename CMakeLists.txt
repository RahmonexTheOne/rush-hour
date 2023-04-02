cmake_minimum_required(VERSION 3.11)
project(rush_hour_etu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")

include_directories(librairies)

configure_file(Sujet/puzzle.txt ${PROJECT_BINARY_DIR}/puzzle.txt COPYONLY)

add_executable(rush-hour
        src/main.cpp
        src/Coordonnees.cpp
        src/Voiture.cpp
        src/Situation.cpp
        src/Noeud.cpp
        src/Graphe.cpp)

