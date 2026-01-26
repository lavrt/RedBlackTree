find_package(GTest REQUIRED)

set(SOURCES
    main.cpp
    test_tree.cpp
)

add_executable(run_unit_tests ${SOURCES})

target_include_directories(run_unit_tests
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(run_unit_tests GTest::gtest GTest::gtest_main)

target_compile_definitions(run_unit_tests
    PRIVATE
        $<$<CONFIG:Debug>:RBTREE_DEBUG=1>
)

include(GoogleTest)
gtest_discover_tests(run_unit_tests)
