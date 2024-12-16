cmake_minimum_required(VERSION 3.16)

# TODO
# execute_process(
#     COMMAND git describe --tags --abbrev=0
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#     OUTPUT_VARIABLE GIT_TAG
#     OUTPUT_STRIP_TRAILING_WHITESPACE
# )
# string(REGEX REPLACE "^v" "" GIT_TAG_CLEANED "${GIT_TAG}")
# message(STATUS "Version of the project is ${GIT_TAG_CLEANED}")
# project(GameOfLife LANGUAGES CXX VERSION ${GIT_TAG_CLEANED})
project(GameOfLife LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

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
    # TODO Wnrvo for gcc14 and up
    add_compile_options(-Wall -Wextra)
    #    TODO coverage should be specific
    #    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 --coverage")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
endif ()


# Set the default build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build: Debug or Release" FORCE)
endif ()

add_library(InputCheckerLib STATIC
        src/Back/InputChecker.cpp
        src/Back/InputChecker.hpp
)

add_library(GameLib STATIC
        src/Back/Game/Game.cpp
        src/Back/Game/Game.hpp
        src/Back/Game/Board.cpp
        src/Back/Game/Board.hpp
        src/Back/Game/Cell.hpp
        src/Back/Game/Parser.cpp
        src/Back/Game/Parser.hpp
        src/Back/Game/OutputWriter.cpp
        src/Back/Game/OutputWriter.hpp
        src/Back/Game/AllowedChar.hpp
        src/Back/Game/PatternList.hpp
)

add_executable(GameOfLife src/Back/gameOfLife.cpp)
target_link_libraries(GameOfLife PRIVATE GameLib InputCheckerLib)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml QuickControls2 Svg Test)

# generation of all patterns and retrieve all in a variable for the QML
add_executable(generatePatternsSvg src/Back/SvgGenerator/generatePatternsSvg.cpp)
target_link_libraries(generatePatternsSvg PRIVATE Qt6::Core Qt6::Svg GameLib)
target_include_directories(generatePatternsSvg PRIVATE ${CMAKE_SOURCE_DIR}/src/Back/Game)

add_custom_target(RunGeneratePatterns ALL
       COMMAND generatePatternsSvg
       COMMENT "Generating all the SVG files of the lexicon ...")


set(GENERATED_SVGS_DIR ${CMAKE_SOURCE_DIR}/src/Front/assets/svg/lexicon)
# Collect all SVG files
file(GLOB GENERATED_SVG_FILES "${GENERATED_SVGS_DIR}/*.svg")

# Generate a newline-separated list of absolute paths
set(ALL_SVG_PATHS "")
foreach (SVG_FILE ${GENERATED_SVG_FILES})
    file(RELATIVE_PATH REL_SVG_FILE ${CMAKE_SOURCE_DIR} ${SVG_FILE})
    list(APPEND ALL_SVG_PATHS ${REL_SVG_FILE})
endforeach ()

add_library(BridgeLib STATIC
        src/Front/Bridge/UIBridge.hpp
        src/Front/Bridge/UIBridge.cpp
        src/Front/Bridge/ThreadProxy.cpp
        src/Front/Bridge/ThreadProxy.hpp
        src/Front/Bridge/LexiconModel.hpp
        src/Front/Bridge/LexiconModel.cpp
        src/Front/Bridge/MainGridImageProvider.cpp
        src/Front/Bridge/MainGridImageProvider.hpp
)
target_include_directories(BridgeLib PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(BridgeLib PRIVATE Qt6::Quick Qt6::Core Qt6::Svg GameLib)


qt_add_executable(appQtGameOfLife src/Front/main.cpp)
#add_dependencies(appQtGameOfLife RunGeneratePatterns) # TODO uncomment me

qt_add_qml_module(appQtGameOfLife
        URI QtGameOfLife
        VERSION ${PROJECT_VERSION}
        RESOURCES src/Front/assets/svg/buttons/clear.svg src/Front/assets/svg/buttons/explanation.svg src/Front/assets/svg/buttons/lexicon.svg src/Front/assets/svg/buttons/next_white.svg src/Front/assets/svg/buttons/next_blue.svg src/Front/assets/svg/buttons/reset.svg src/Front/assets/svg/buttons/speed-gauge.svg src/Front/assets/svg/buttons/start.svg src/Front/assets/svg/buttons/grid.svg src/Front/assets/svg/buttons/stop.svg src/Front/assets/lexicon.txt src/Front/assets/png/example_1.1.png src/Front/assets/png/example_1.2.png src/Front/assets/png/example_2.1.png src/Front/assets/png/example_2.2.png src/Front/assets/png/example_3.1.png src/Front/assets/png/example_3.2.png src/Front/assets/png/example_5.1.png src/Front/assets/png/example_5.2.png src/Front/assets/png/yt-hawkins.jpg src/Front/assets/png/yt-numberphile.jpg
        QML_FILES src/Front/Main.qml src/Front/QMLComponents/ActionButton.qml src/Front/QMLComponents/GameSliders.qml src/Front/QMLComponents/GameGrid.qml src/Front/QMLComponents/CustomImage.qml src/Front/QMLComponents/CustomSlider.qml src/Front/QMLComponents/Overlay.qml src/Front/QMLComponents/GenericPopUp.qml src/Front/QMLComponents/CustomText.qml src/Front/QMLComponents/LexiconElements.qml src/Front/QMLComponents/ExplanationElements.qml src/Front/QMLComponents/ExplanationExamples.qml
        # Lexicon Resources
        RESOURCES ${ALL_SVG_PATHS}
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtGameOfLife PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER appQtGameOfLife
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)


target_link_libraries(appQtGameOfLife PRIVATE Qt6::Quick BridgeLib)

target_include_directories(appQtGameOfLife PRIVATE ${CMAKE_SOURCE_DIR}/src)

install(TARGETS appQtGameOfLife
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin
)

qt_generate_deploy_qml_app_script(
    TARGET appQtGameOfLife
    OUTPUT_SCRIPT deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})


option(ENABLE_ASAN "Enable AddressSanitizer with ON" OFF)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Compiling in Debug mode. Preparing targets for unit tests and functional tests")
    enable_testing()
    add_compile_definitions(ENABLE_DEBUG)

    include(${CMAKE_BINARY_DIR}/_deps/conan_toolchain.cmake)

    find_package(GTest REQUIRED CONFIG)


    add_executable(GameOfLifeUnitTests
            tests/Back/unit_tests.cpp
            tests/InputsBoards.hpp
            tests/Back/tests_utilities.hpp
            tests/Back/tests_utilities.cpp
            tests/Back/unit_tests/InputChecker_Test.cpp
            tests/Back/unit_tests/OutputWriter_Test.cpp
            tests/Back/unit_tests/Game_Test.cpp
            tests/Back/unit_tests/Board_Test.cpp
            tests/Back/unit_tests/Parser_Test.cpp
            tests/Back/unit_tests/AllowedChar_Test.cpp
            tests/Back/unit_tests/PatternList_Test.cpp
    )

    if (MSVC)
        target_link_libraries(GameOfLifeUnitTests PRIVATE InputCheckerLib GameLib GTest::gtest_main GTest::gtest)
    else ()
        #        TODO gcov shall be specific
        #        target_link_libraries(GameOfLifeUnitTests PRIVATE InputCheckerLib GameLib GTest::gtest_main GTest::gtest gcov)
        target_link_libraries(GameOfLifeUnitTests PRIVATE InputCheckerLib GameLib GTest::gtest_main GTest::gtest)
    endif ()

    target_include_directories(GameOfLifeUnitTests PUBLIC ${CMAKE_SOURCE_DIR}/src)

    add_test(NAME GameOfLifeUnitTests COMMAND GameOfLifeUnitTests)

    add_executable(GameOfLifeFunctionalTests
            tests/Back/functional_tests.cpp
            tests/InputsBoards.hpp
            tests/Back/tests_utilities.hpp
            tests/Back/tests_utilities.cpp
    )

    if (MSVC)
        target_link_libraries(GameOfLifeFunctionalTests PRIVATE InputCheckerLib GameLib GTest::gtest_main GTest::gtest)
    else ()
        #        TODO gcov shall be specific
        #        target_link_libraries(GameOfLifeFunctionalTests PRIVATE InputCheckerLib GameLib GTest::gtest_main GTest::gtest gcov)
        target_link_libraries(GameOfLifeFunctionalTests PRIVATE InputCheckerLib GameLib GTest::gtest_main GTest::gtest)
    endif ()

    target_include_directories(GameOfLifeFunctionalTests PUBLIC ${CMAKE_SOURCE_DIR}/src)
    add_test(NAME GameOfLifeFunctionalTests COMMAND GameOfLifeFunctionalTests)


    add_executable(GameOfLifeGUIUnitTests
            tests/Front/unit_tests.cpp
            tests/InputsBoards.hpp
            tests/Front/tests_utilities.hpp
            tests/Front/tests_utilities.cpp
            tests/Back/tests_utilities.hpp
            tests/Back/tests_utilities.cpp
            tests/Front/Bridge/ThreadProxy_Test.cpp
            tests/Front/Bridge/LexiconModel_Test.cpp
            tests/Front/Bridge/MainGridImageProvider_Test.cpp
    )

    if (MSVC)
        target_link_libraries(GameOfLifeGUIUnitTests PRIVATE BridgeLib Qt6::Quick Qt6::Test GTest::gtest_main GTest::gtest)
    else ()
        #        TODO gcov shall be specific
        #        target_link_libraries(GameOfLifeGUIUnitTests PRIVATE BridgeLib Qt6::Quick Qt6::Test GTest::gtest_main GTest::gtest gcov)
        target_link_libraries(GameOfLifeGUIUnitTests PRIVATE BridgeLib Qt6::Quick Qt6::Test GTest::gtest_main GTest::gtest)
    endif ()

    target_include_directories(GameOfLifeGUIUnitTests PUBLIC ${CMAKE_SOURCE_DIR}/src)
    add_test(NAME GameOfLifeGUIUnitTests COMMAND GameOfLifeGUIUnitTests)
endif ()

if (ENABLE_ASAN STREQUAL "ON" AND (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"))
    message(STATUS "Enable Address Sanitizer")
    set(SANITIZE_FLAGS "-fsanitize-address-use-after-scope -fno-omit-frame-pointer -fsanitize=address,undefined,bounds")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") #GCC
        set(SANITIZE_FLAGS "${SANITIZE_FLAGS},leak")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_SYSTEM_NAME MATCHES "Darwin")# Clang, but not Apple Clang
        set(SANITIZE_FLAGS "${SANITIZE_FLAGS},leak")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZE_FLAGS}")
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
            target_link_libraries(appQtGameOfLife PRIVATE ${PROFILER_LIB})
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
            target_link_libraries(appQtGameOfLife PRIVATE ${PROFILER_LIB})
        else ()
            message(FATAL_ERROR "gperftools tcmalloc not found")
        endif ()
    elseif (PROFILING_TYPE STREQUAL "none")
        message(STATUS "No profiling library selected")
    else ()
        message(STATUS "Option PROFILING_TYPE not fulfilled, consider none (no profiling)")
    endif ()
endif ()
