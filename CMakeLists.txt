cmake_minimum_required(VERSION 3.15)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set flags or configurations specific to Debug and Release
# Detect the compiler and apply specific flags
if (MSVC)
    # MSVC-specific flags
    add_compile_options(/W4 /MP)  # W4 This is roughly equivalent to -Wall and -Wextra in GCC/Clang
    set(CMAKE_CXX_FLAGS_DEBUG "/DEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/DEBUG /O2")
else ()
    # GCC/Clang specific flags
    add_compile_options(-Wall -Wextra)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 --coverage")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
endif ()


# Set the default build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build: Debug or Release" FORCE)
endif ()

add_library(InputCheckerLib STATIC
        src/InputChecker.cpp
        src/InputChecker.hpp
)

add_library(GameLib STATIC
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
target_link_libraries(GameOfLife PRIVATE GameLib InputCheckerLib)


option(ENABLE_ASAN "Enable AddressSanitizer with ON" OFF)

if (MSVC)
    option(CMAKE_CONFIGURATION "Configuration for the build to come")
endif ()

message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Compiling in Debug mode. Preparing targets for unit tests and functional tests")
    enable_testing()
    add_compile_definitions(ENABLE_DEBUG)

    include(${CMAKE_BINARY_DIR}/_deps/conan_toolchain.cmake)
    find_package(GTest REQUIRED CONFIG)

    add_executable(GameOfLifeUnitTests
            tests/unit_tests.cpp
            tests/tests_utilities.hpp
            tests/tests_utilities.cpp
            tests/unit_tests/InputChecker_Test.cpp
            tests/unit_tests/OutputWriter_Test.cpp
            tests/unit_tests/Game_Test.cpp
            tests/unit_tests/Board_Test.cpp
            tests/unit_tests/Parser_Test.cpp
    )

    if (MSVC)
        target_link_libraries(GameOfLifeUnitTests PRIVATE GTest::gtest InputCheckerLib GameLib)
    else ()
        target_link_libraries(GameOfLifeUnitTests PRIVATE GTest::gtest InputCheckerLib GameLib gcov)
    endif ()

    target_include_directories(GameOfLifeUnitTests PUBLIC ${CMAKE_SOURCE_DIR}/src)

    add_test(NAME GameOfLifeUnitTests COMMAND GameOfLifeUnitTests)

    add_executable(GameOfLifeFunctionalTests
            tests/functional_tests.cpp
            tests/tests_utilities.hpp
            tests/tests_utilities.cpp
    )

    if (MSVC)
        target_link_libraries(GameOfLifeFunctionalTests PRIVATE gtest::gtest InputCheckerLib GameLib)
    else ()
        target_link_libraries(GameOfLifeFunctionalTests PRIVATE gtest::gtest InputCheckerLib GameLib gcov)
    endif ()

    target_include_directories(GameOfLifeFunctionalTests PUBLIC ${CMAKE_SOURCE_DIR}/src)
    add_test(NAME GameOfLifeFunctionalTests COMMAND GameOfLifeFunctionalTests)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    option(PROFILING_TYPE "Select which profiler to use (none, cpu, heap)" "none")

    if (PROFILING_TYPE STREQUAL "cpu")
        find_library(PROFILER_LIB profiler)
        if (PROFILER_LIB)
            message(STATUS "Linking with gperftools profiler for CPU profiling")
            add_compile_definitions(ENABLE_CPU_PROFILING)
            set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-lprofiler")
            target_link_libraries(GameOfLife PRIVATE ${PROFILER_LIB})
        else ()
            message(FATAL_ERROR "gperftools profiler not found")
        endif ()
    elseif (PROFILING_TYPE STREQUAL "heap")
        find_library(TCMALLOC_LIB tcmalloc)
        if (TCMALLOC_LIB)
            message(STATUS "Linking with gperftools tcmalloc for Heap profiling")
            add_compile_definitions(ENABLE_HEAP_PROFILING)
            set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-ltcmalloc")
            target_link_libraries(GameOfLife PRIVATE ${TCMALLOC_LIB})
        else ()
            message(FATAL_ERROR "gperftools tcmalloc not found")
        endif ()
    elseif (PROFILING_TYPE STREQUAL "none")
        message(STATUS "No profiling library selected")
    else ()
        message(STATUS "Option PROFILING_TYPE not fulfilled, consider none (no profiling)")
    endif ()
endif ()

if (ENABLE_ASAN STREQUAL "ON" AND (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"))
    message(STATUS "Enable Address Sanitizer")
    set(CMAKE_CXX_FLAGS "-fsanitize=address,undefined,leak,bounds -fsanitize-address-use-after-scope -fno-omit-frame-pointer")
endif ()