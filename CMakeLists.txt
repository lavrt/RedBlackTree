cmake_minimum_required(VERSION 3.11)
project(rbt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

# tree ---------------------------------------

add_executable(tree src/main.cpp)

target_include_directories(tree
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# comparator ---------------------------------

add_executable(compare src/comparator.cpp)

target_include_directories(compare
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
