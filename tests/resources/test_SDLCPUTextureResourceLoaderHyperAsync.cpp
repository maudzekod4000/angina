#include <gtest/gtest.h>

#include <string>
#include <filesystem>
#include <vector>
#include <chrono>
#include <algorithm>

#include "backend/sdl/resources/SDLCPUTextureResourceLoaderHyperAsync.h"

using namespace Backend::SDL::Resources;

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

TEST(SDLCPUTextureResourceHyperAsync, Init)
{
    SDLCPUTextureLoaderHyperAsync loader;

    EXPECT_TRUE(&loader);
}

TEST(SDLCPUTextureResourceHyperAsync, Load)
{
    SDLCPUTextureLoaderHyperAsync loader;
    const std::string path = std::string(TEST_RESOURCE_DIR) + "/Bishop_W.png";

    auto start = std::chrono::steady_clock::now();
    const auto idOrErr = loader.load(path);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading texture took: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    EXPECT_TRUE(idOrErr.has_value());
    auto id = idOrErr.value();

    std::thread([id, &loader]() {
        
        while (!loader.isValid(id)) {
            std::cout << "Texture is not available yet" << std::endl;
        }
    }).join();

    EXPECT_TRUE(loader.isValid(id));
}

TEST(SDLCPUTextureResourceHyperAsync, LoadTwo)
{
    SDLCPUTextureLoaderHyperAsync loader;
    const std::filesystem::path path1 = std::string(TEST_RESOURCE_DIR) + "/Bishop_W.png";
    const std::filesystem::path path2 = std::string(TEST_RESOURCE_DIR) + "/Bishop_B.png";
    
    auto start = std::chrono::steady_clock::now();
    const auto ids = loader.load(std::vector({ path1, path2 }));
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading textures took: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    EXPECT_TRUE(ids[0].has_value());
    auto id1 = ids[0].value();

    EXPECT_TRUE(ids[1].has_value());
    auto id2 = ids[1].value();

    std::thread([id1, id2, &loader]() {
        while (loader.isValid(id1) == false || loader.isValid(id2) == false) {
            std::cout << "Texture with id: " << id1 << " is loaded = " << loader.isValid(id1) << std::endl;
            std::cout << "Texture with id: " << id2 << " is loaded = " << loader.isValid(id2) << std::endl;
        }
    }).join();

    EXPECT_TRUE(loader.isValid(id1));
    EXPECT_TRUE(loader.isValid(id2));
}

TEST(SDLCPUTextureResourceHyperAsync, LoadManyResolveOne)
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

    SDLCPUTextureLoaderHyperAsync loader;

    auto start = std::chrono::steady_clock::now();
    const auto ids = loader.load(texFilePaths50);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading textures took: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    std::thread([ids, &loader]() {

        // TODO: This is not cool, because some resources might just fail to load
        // and this will clog the whole test execution forever...
        while (!std::all_of(ids.begin(), ids.end(), [&loader](auto idOrErr) { return loader.isValid(idOrErr.value()); })) {
            std::cout << "Texture is not available yet" << std::endl;
        }
    }).join();

    auto texLoadedEnd = std::chrono::steady_clock::now();
    std::cout << "Loading texture took: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(texLoadedEnd - start).count() <<
        " ms." << std::endl;

    EXPECT_TRUE(std::all_of(ids.begin(), ids.end(), [&loader](auto idOrErr) { return loader.isValid(idOrErr.value()); }));
}
