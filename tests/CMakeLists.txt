cmake_minimum_required(VERSION 3.0)

project(P3HashTester)

set(CMAKE_CXX_STANDARD 17)

include_directories(${P3HashLib_SOURCE_DIR})

add_executable(
    DebugTests 
    libtests.cpp
)

add_executable(
    ReleaseTests 
    libtests.cpp
)

target_link_libraries(DebugTests P3HashShared)
target_link_libraries(ReleaseTests P3HashShared)

add_test(
    NAME P3HashDebugTests
    COMMAND DebugTests
    CONFIGURATIONS Debug
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)

add_test(
    NAME P3HashReleaseTests
    COMMAND ReleaseTests
    CONFIGURATIONS Release
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)