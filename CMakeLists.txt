cmake_minimum_required(VERSION 3.20)
project(yazi C)

set(CMAKE_C_STANDARD 11)

add_executable(yazi
        main.c
        memory.c
        helpers.c)
