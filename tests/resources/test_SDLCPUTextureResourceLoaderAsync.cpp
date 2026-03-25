#include <gtest/gtest.h>

#include <string>
#include <chrono>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include "backend/sdl/resources/SDLCPUTextureResourceLoaderAsync.h"

using namespace Backend::SDL::Resources;

// Note: Always use isValid before calling release or resolve!
// Tests are like usage examples.

static std::vector<std::filesystem::path> loadFileNames(const std::filesystem::path& dir)
{
    std::vector<std::filesystem::path> res;

    if (std::filesystem::is_directory(dir) == false || std::filesystem::exists(dir) == false) {
        return res;
    }

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            res.push_back(entry.path());
        }
    }

    return res;
}

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
