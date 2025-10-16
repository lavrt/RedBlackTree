cmake_minimum_required(VERSION 3.11)
project(rbt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# tree ---------------------------------------

add_executable(tree src/main.cpp)

target_include_directories(tree
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# comparator ---------------------------------

add_executable(compare comparator/main.cpp)

target_include_directories(compare
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# tests --------------------------------------

enable_testing()
add_subdirectory(tests)
