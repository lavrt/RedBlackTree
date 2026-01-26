add_executable(run_reference reference/reference.cpp)

target_include_directories(run_reference
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(run_reference
    PRIVATE
        $<$<CONFIG:Debug>:RBTREE_DEBUG=1>
)

add_executable(execute execution/main.cpp)

target_include_directories(execute
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(execute
    PRIVATE
        $<$<CONFIG:Debug>:RBTREE_DEBUG=1>
)
