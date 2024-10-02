#!/bin/bash

# Default build type
BUILD_TYPE="Release"
BUILD_DIR="build-release"

# Parse command-line options
usage() {
    echo "ERROR in arguments. Please use one of the following: $0 [-c <Debug|Release|RelWithDebInfo> for the configuration you want for the binary] [-p <heap|cpu|none> for choosing the profiling binary you want] [-a for enabling address sanitizer ] [-s for static analysis]"
    exit 1
}


while getopts ":c:p:as" opt; do
    case ${opt} in
        c)
            BUILD_TYPE=$OPTARG
            ;;
        s)
            STATIC_ANALYSIS='-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -D CMAKE_CXX_CLANG_TIDY="clang-tidy;-checks=*,-clang-analyzer-alpha.*"'
            ;;
        p)
            PROFILING_TYPE="-DPROFILING_TYPE=$OPTARG"
            ;;
        a)
            ASAN="-DENABLE_ASAN=ON"
            ;;
        *)
            usage
            ;;
    esac
done


if [ "$BUILD_TYPE" == "Debug" ]; then
    BUILD_DIR="build-debug"
elif [ "$BUILD_TYPE" == "RelWithDebInfo" ]; then
    BUILD_DIR="build-relwithdebinfo"
elif [ "$BUILD_TYPE" != "Release" ]; then
    echo "Invalid build type: $BUILD_TYPE"
    usage
fi

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE $PROFILING_TYPE $ASAN -Wno-dev .. 
cmake --build . -- -j