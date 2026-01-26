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

target_compile_definitions(tree
    PRIVATE
        $<$<CONFIG:Debug>:RBTREE_DEBUG=1>
)

# comparator ---------------------------------

add_executable(compare comparator/main.cpp)

target_include_directories(compare
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(compare
    PRIVATE
        $<$<CONFIG:Debug>:RBTREE_DEBUG=1>
)

# tests --------------------------------------

enable_testing()
add_subdirectory(tests)
