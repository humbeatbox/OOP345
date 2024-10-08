cmake_minimum_required(VERSION 3.28)
project(ws2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ws2 main.cpp
        health.h
        character.h
        team.cpp
        team.h
        guild.cpp
        guild.h
        barbarian.h
        rogue.h
        abilities.h
        weapons.h
        archer.h)
