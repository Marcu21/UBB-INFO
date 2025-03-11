cmake_minimum_required(VERSION 3.27)
project(oop_lab5_marcus C)

set(CMAKE_C_STANDARD 11)

add_executable(oop_lab5_marcus
        domain.h
        domain.c
        lab2.c
        ui.c
        tests.c
        service.c
        repo.c)
