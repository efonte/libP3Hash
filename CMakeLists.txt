cmake_minimum_required(VERSION 3.0)

project(LibP3Hash)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LibP3Hash_SOURCE_DIR}/bin/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${LibP3Hash_SOURCE_DIR}/lib/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LibP3Hash_SOURCE_DIR}/lib/Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LibP3Hash_SOURCE_DIR}/bin/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LibP3Hash_SOURCE_DIR}/lib/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LibP3Hash_SOURCE_DIR}/lib/Release)

include_directories(${LibP3Hash_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(src)
add_subdirectory(sample)
add_subdirectory(tests)