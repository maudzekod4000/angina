add_executable(tests
    test_something.cpp
    test_FreeList.cpp
    resources/test_SDLCPUTextureResourceLoader.cpp
    resources/test_SDLCPUTextureResourceLoaderAsync.cpp
    resources/test_SDLCPUTextureResourceLoaderHyperAsync.cpp
    resources/test_CPUTextureLoadWorker.cpp
    resources/test_GPUTextureLoader.cpp
    platform/test_BaseInputEventManager.cpp

    helpers/file.h
    helpers/file.cpp
)

target_include_directories(tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(tests
    PRIVATE
        project_options
        core
        sdl
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

target_compile_definitions(tests
    PRIVATE
        TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/testfiles")
