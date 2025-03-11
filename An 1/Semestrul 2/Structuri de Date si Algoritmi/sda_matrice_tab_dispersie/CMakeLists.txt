cmake_minimum_required(VERSION 3.28)
project(sda_matrice_tab_dispersie)

set(CMAKE_CXX_STANDARD 17)

add_executable(sda_matrice_tab_dispersie App.cpp
        Matrice.cpp
        TestExtins.cpp
        TestScurt.cpp)
