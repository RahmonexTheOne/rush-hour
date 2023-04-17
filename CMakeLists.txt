cmake_minimum_required(VERSION 3.11)
project(rush-hour)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")

include_directories(librairies)

add_executable(rush-hour
        src/main.cpp
        src/board.cpp
        src/place.cpp
        src/car.cpp)

