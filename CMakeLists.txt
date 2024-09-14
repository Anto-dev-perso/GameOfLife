cmake_minimum_required(VERSION 3.22)
project(GameOfLife)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_library(InputCheckerLib SHARED
        src/InputChecker.cpp
        src/InputChecker.hpp
        )

add_library(GameLib SHARED
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Game/Board.cpp
        src/Game/Board.hpp
        src/Game/Cell.cpp
        src/Game/Cell.hpp
        src/Game/Parser.cpp
        src/Game/Parser.hpp
        src/Game/OutputWriter.cpp
        src/Game/OutputWriter.hpp
        )

add_executable(GameOfLife src/gameOfLife.cpp)
target_link_libraries(GameOfLife InputCheckerLib GameLib)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(GameOfLifeTests
        tests/test.cpp
        tests/unit_tests/InputChecker_Test.cpp
        )

target_link_libraries(GameOfLifeTests PRIVATE gtest_main InputCheckerLib GameLib)
target_include_directories(GameOfLifeTests PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_test(NAME GameOfLifeTests COMMAND GameOfLifeTests)
