cmake_minimum_required(VERSION 2.8)
project(Puhe C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")
set(CMAKE_MODULE_PATH "${PROJECT_BINARY_DIR}/cmake/" ${CMAKE_MODULE_PATH})

option(DEBUG "Compile in debug mode" OFF)

if(DEBUG)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -g3 -pg -std=c++11 -fprofile-arcs -ftest-coverage")
else(DEBUG)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -O3 -std=c++11 -DNDEBUG")
endif(DEBUG)

if(MINGW)
    set(CMAKE_CXX_FLAGS "-mwindows ${CMAKE_CXX_FLAGS}")
endif(MINGW)

include_directories(
    src
)

file(GLOB SRC_CPP
    src/main.cpp
    src/chain.cpp
)

add_executable(puhe ${SRC_CPP})


