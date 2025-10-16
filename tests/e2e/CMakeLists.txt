add_executable(run_reference reference/reference.cpp)

target_include_directories(run_reference
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(execute execution/main.cpp)

target_include_directories(execute
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)
