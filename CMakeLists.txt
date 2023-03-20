cmake_minimum_required(VERSION 3.0)

project(LibP3Hash)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LibP3Hash_SOURCE_DIR}/bin)

enable_testing()
add_subdirectory(src)
add_subdirectory(sample)
add_subdirectory(tests)