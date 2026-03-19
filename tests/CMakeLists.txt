add_executable(tests
    test_something.cpp
    test_FreeList.cpp
)

target_link_libraries(tests
    PRIVATE
        project_options
        core
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
