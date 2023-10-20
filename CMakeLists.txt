cmake_minimum_required(VERSION 3.26)
project(p4)

set(CMAKE_CXX_STANDARD 17)

add_executable(p4 main.cpp
        node.cpp
        node.h
        graph.cpp
        graph.h
        database.cpp
        database.h)
