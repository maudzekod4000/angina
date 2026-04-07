#include <gtest/gtest.h>

#include <string>
#include <chrono>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include "backend/sdl/resources/SDLCPUTextureResourceLoaderAsync.h"

#include "helpers/file.h"

using namespace Backend::SDL::Resources;
using namespace Test::Helpers::File;

// Note: Always use isValid before calling release or resolve!
// Tests are like usage examples.

TEST(SDLCPUTextureResourceAsync, Init)
{
    SDLCPUTextureLoaderAsync texLoader;

    EXPECT_TRUE(&texLoader);
}

TEST(SDLCPUTextureResourceAsync, Load10)
{
    const std::string dir = std::string(TEST_RESOURCE_DIR) + "/textures10";
    const std::vector<std::filesystem::path> texFilePaths = loadFileNames(dir);

    EXPECT_EQ(10, texFilePaths.size());

    SDLCPUTextureLoaderAsync texLoader;

    auto start = std::chrono::steady_clock::now();
    auto idsOrErrors = texLoader.load(texFilePaths);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading textures took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    EXPECT_EQ(10, idsOrErrors.size());

    for (const auto& idOrError : idsOrErrors) {
        EXPECT_TRUE(idOrError.has_value());
    }
}

TEST(SDLCPUTextureResourceAsync, Load50)
{
    const std::string dir = std::string(TEST_RESOURCE_DIR) + "/textures10";
    const std::vector<std::filesystem::path> texFilePaths = loadFileNames(dir);

    std::vector<std::filesystem::path> texFilePaths50;
    texFilePaths50.reserve(texFilePaths.size() * 5);

    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());

    EXPECT_EQ(50, texFilePaths50.size());

    SDLCPUTextureLoaderAsync texLoader;

    auto start = std::chrono::steady_clock::now();
    auto idsOrErrors = texLoader.load(texFilePaths50);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading textures took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    EXPECT_EQ(50, idsOrErrors.size());

    for (const auto& idOrError : idsOrErrors) {
        EXPECT_TRUE(idOrError.has_value());
    }
}
