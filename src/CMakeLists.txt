project(P3HashLib)

add_library(
    P3HashShared
    SHARED
    libP3Hash.cpp
)

add_library(
    P3HashStatic
    STATIC
    libP3Hash.cpp
)