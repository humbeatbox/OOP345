cmake_minimum_required(VERSION 3.28)
project(ws3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ws3 tester_1.cpp
        mediaItem.h
        settings.cpp
        settings.h
        book.cpp
        book.h
        movie.cpp
        movie.h
        tvShow.cpp
        tvShow.h
        spellChecker.cpp
        spellChecker.h
        collection.cpp
        collection.h
        tvShow.cpp)
