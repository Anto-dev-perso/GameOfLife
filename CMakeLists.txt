project(GameOfLife LANGUAGES CXX)
cmake_minimum_required(VERSION 3.0)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra)

# Set flags or configurations specific to Debug and Release
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 --coverage")
# set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 --coverage -fsanitize=address,undefined -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")

# Linker flags for Debug (with sanitizers)
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-fsanitize=address,undefined")


# Set the default build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build: Debug or Release" FORCE)
endif ()

add_library(InputCheckerLib SHARED
        src/InputChecker.cpp
        src/InputChecker.hpp
        )

add_library(GameLib SHARED
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Game/Board.cpp
        src/Game/Board.hpp
        src/Game/Cell.hpp
        src/Game/Parser.cpp
        src/Game/Parser.hpp
        src/Game/OutputWriter.cpp
        src/Game/OutputWriter.hpp
        src/Game/AllowedChar.hpp
        )

add_executable(GameOfLife src/gameOfLife.cpp)
target_link_libraries(GameOfLife InputCheckerLib GameLib)


# Register the test target with CTest (for Debug mode)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(FetchContent)


    FetchContent_Declare(
           googletest
           # Specify the commit you depend on and update it regularly.
           URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(GameOfLifeUnitTests
            tests/unit_tests.cpp
            tests/unit_tests/InputChecker_Test.cpp
            tests/unit_tests/OutputWriter_Test.cpp
            tests/unit_tests/Game_Test.cpp
            tests/unit_tests/Board_Test.cpp
            tests/unit_tests/Parser_Test.cpp
            )
    target_link_libraries(GameOfLifeUnitTests PRIVATE gtest_main InputCheckerLib GameLib gcov)
    target_include_directories(GameOfLifeUnitTests PUBLIC ${CMAKE_SOURCE_DIR}/src)
    add_test(NAME GameOfLifeUnitTests COMMAND GameOfLifeUnitTests)

    add_executable(GameOfLifeFunctionalTests
            tests/functional_tests.cpp
            tests/tests_utilities.hpp
            tests/tests_utilities.cpp
            )

    target_link_libraries(GameOfLifeFunctionalTests PRIVATE gtest_main InputCheckerLib GameLib gcov)
    target_include_directories(GameOfLifeFunctionalTests PUBLIC ${CMAKE_SOURCE_DIR}/src)
    add_test(NAME GameOfLifeFunctionalTests COMMAND GameOfLifeFunctionalTests)
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    option(PROFILING_TYPE "Select which profiler to use (none, cpu, heap)" "none")

    if(PROFILING_TYPE STREQUAL "cpu")
            find_library(PROFILER_LIB profiler)
            if(PROFILER_LIB)
                    message(STATUS "Linking with gperftools profiler for CPU profiling")
                    target_compile_definitions(GameOfLife PRIVATE ENABLE_CPU_PROFILING=1) 
                    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-lprofiler")
                    target_link_libraries(GameOfLife ${PROFILER_LIB})
                    else()
                    message(FATAL_ERROR "gperftools profiler not found")
                    endif()
                    elseif(PROFILING_TYPE STREQUAL "heap")
                    find_library(TCMALLOC_LIB tcmalloc)
                    if(TCMALLOC_LIB)
                    message(STATUS "Linking with gperftools tcmalloc for Heap profiling")
                    target_compile_definitions(GameOfLife PRIVATE ENABLE_HEAP_PROFILING=1) 
                    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-ltcmalloc")
                    target_link_libraries(GameOfLife ${TCMALLOC_LIB})
            else()
                    message(FATAL_ERROR "gperftools tcmalloc not found")
            endif()
    elseif(PROFILING_TYPE STREQUAL "none")
            message(STATUS "No profiling library selected")
    else()
            message(STATUS "Option PROFILING_TYPE not fulfilled, consider none (no profiling)")
    endif()
endif()
