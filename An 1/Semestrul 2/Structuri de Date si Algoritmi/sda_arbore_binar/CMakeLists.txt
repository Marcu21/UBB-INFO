cmake_minimum_required(VERSION 3.28)
project(sda_arbore_binar)

set(CMAKE_CXX_STANDARD 17)

add_executable(sda_arbore_binar App.cpp
        AB.cpp
        IteratorAB.cpp
        TestExtins.cpp
        TestScurt.cpp)
