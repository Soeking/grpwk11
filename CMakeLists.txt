cmake_minimum_required(VERSION 3.15)
project(grpwk11 C)

set(CMAKE_C_STANDARD 99)

add_executable(grpwk11
        src/main.c
        src/read.c src/read.h
        src/strings.c src/strings.h
        src/search.c src/search.h
        src/processing.c src/processing.h
        )