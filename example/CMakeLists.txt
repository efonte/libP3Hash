cmake_minimum_required(VERSION 3.0)

project(lib-example)

set(CMAKE_CXX_STANDARD 17)

# or maybe not?
include_directories(${P3HashLib_SOURCE_DIR})

add_executable(
    P3Hasher
    P3Hasher.cpp
)

target_link_libraries(P3Hasher P3Hash)