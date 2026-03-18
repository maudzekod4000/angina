add_executable(tests
    test_something.cpp
)

target_link_libraries(tests
    PRIVATE
        core
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
