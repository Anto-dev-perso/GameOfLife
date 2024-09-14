cmake_minimum_required(VERSION 3.22)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(GameOfLife_sources main.cpp
        InputChecker.cpp
        InputChecker.hpp
        Game/Game.cpp
        Game/Game.hpp
        Game/Board.cpp
        Game/Board.hpp
        Game/Cell.cpp
        Game/Cell.hpp
        Game/Parser.cpp
        Game/Parser.hpp
        Game/OutputWriter.cpp Game/OutputWriter.hpp)

add_executable(GameOfLife ${GameOfLife_sources})
