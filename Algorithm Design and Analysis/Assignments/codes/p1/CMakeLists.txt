cmake_minimum_required(VERSION 3.26)
project(p1)

set(CMAKE_CXX_STANDARD 11)

add_executable(p1 1.cpp 2.cpp
        3.cpp
        4.cpp)

add_executable(1 1.cpp)
add_executable(2 2.cpp)
add_executable(3 3.cpp)
add_executable(4 4.cpp)