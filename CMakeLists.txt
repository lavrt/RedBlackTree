cmake_minimum_required(VERSION 3.11)
project(rbt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND 
   CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")
endif()

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
