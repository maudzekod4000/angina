#include <gtest/gtest.h>

#include <string>
#include <filesystem>
#include <vector>

#include "backend/sdl/resources/SDLCPUTextureResourceLoader.h"

#include "helpers/file.h"

using namespace Backend::SDL::Resources;
using namespace Test::Helpers::File;

// Note: Always use isValid before calling release or resolve!
// Tests are like usage examples.

TEST(SDLCPUTextureResource, Init)
{
    SDLCPUTextureResourceLoader texLoader;

    EXPECT_TRUE(&texLoader);
}

// 1. Test that we can load a resource and get a handle to it.
TEST(SDLCPUTextureResource, Load)
{
    SDLCPUTextureResourceLoader texLoader;

    const std::string path = std::string(TEST_RESOURCE_DIR) + "/Bishop_W.png";

    const auto idOrErr = texLoader.load(path);

    texLoader.wait();

    EXPECT_TRUE(idOrErr.has_value());
    EXPECT_TRUE(texLoader.isValid(idOrErr.value()));
    auto handle = texLoader.resolve(idOrErr.value());
    EXPECT_TRUE(handle.ptr);
}

// 2. Test that we can remove a resource and it is no longer valid (how to check the memory tho)
TEST(SDLCPUTextureResource, Release)
{
    SDLCPUTextureResourceLoader texLoader;

    const std::string path = std::string(TEST_RESOURCE_DIR) + "/Bishop_W.png";

    const auto idOrErr = texLoader.load(path);
    const auto id = idOrErr.value();

    texLoader.wait();

    EXPECT_TRUE(texLoader.isValid(id));
    
    auto err = texLoader.release(id);

    EXPECT_FALSE(err);
    EXPECT_FALSE(texLoader.isValid(id));
}

// 3. Loading an non-existent resource should return a good error
TEST(SDLCPUTextureResource, LoadNonExist)
{
    SDLCPUTextureResourceLoader texLoader;

    const std::string path = std::string(TEST_RESOURCE_DIR) + "/not-really-there.png";

    const auto idOrErr = texLoader.load(path);
    texLoader.wait();

    EXPECT_FALSE(texLoader.isValid(idOrErr.value()));
}

TEST(SDLCPUTextureResource, Load10)
{
    const std::string dir = std::string(TEST_RESOURCE_DIR) + "/textures10";
    const std::vector<std::filesystem::path> texFilePaths = loadFileNames(dir);

    EXPECT_EQ(10, texFilePaths.size());

    SDLCPUTextureResourceLoader texLoader;

    auto start = std::chrono::steady_clock::now();
    auto idsOrErrors = texLoader.load(texFilePaths);
    texLoader.wait();
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading textures took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    EXPECT_EQ(10, idsOrErrors.size());

    for (const auto& idOrError : idsOrErrors) {
        EXPECT_TRUE(idOrError.has_value());
    }
}

TEST(SDLCPUTextureResource, Load50)
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

    SDLCPUTextureResourceLoader texLoader;

    auto start = std::chrono::steady_clock::now();
    auto idsOrErrors = texLoader.load(texFilePaths50);
    texLoader.wait();
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading textures took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    EXPECT_EQ(50, idsOrErrors.size());

    for (const auto& idOrError : idsOrErrors) {
        EXPECT_TRUE(idOrError.has_value());
    }
}
