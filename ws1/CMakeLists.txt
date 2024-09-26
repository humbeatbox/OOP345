cmake_minimum_required(VERSION 3.28)
project(ws1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ws1 main.cpp
        tester_1.cpp
        settings.cpp
        settings.h
        timeMonitor.cpp
        timeMonitor.h
        logger.cpp
        logger.h
        dictionary.cpp
        dictionary.h
        event.cpp
        event.h)
