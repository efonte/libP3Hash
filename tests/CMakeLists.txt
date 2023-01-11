cmake_minimum_required(VERSION 3.0)

project(P3HashTester)

set(CMAKE_CXX_STANDARD 17)

include_directories(${P3HashLib_SOURCE_DIR})

add_executable(
    TestStart 
    libtests.cpp
)

target_link_libraries(TestStart P3Hash)

add_test(
    NAME P3HashTests
    COMMAND TestStart
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)