cmake_minimum_required(VERSION 3.28)
project(ws4)

set(CMAKE_CXX_STANDARD 17)

add_executable(ws4 main.cpp
        Station.cpp
        Station.h
        Utilities.cpp
        Utilities.h)
