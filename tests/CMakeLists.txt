cmake_minimum_required(VERSION 3.0)

project(P3HashTester)

set(CMAKE_CXX_STANDARD 17)

include_directories(${P3HashLib_SOURCE_DIR})

add_executable(
    Tests 
    libtests.cpp
)

target_link_libraries(Tests P3HashShared)

add_test(
    NAME P3HashDebugTests
    COMMAND Tests

    -small 600
    -big 9000
    -inv 2
    -corr 3

    CONFIGURATIONS Debug
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)

add_test(
    NAME P3HashReleaseTests
    COMMAND Tests

    -small 100
    -big 1500
    -inv 2
    -corr 3

    CONFIGURATIONS Release
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)