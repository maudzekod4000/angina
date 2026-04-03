#include <gtest/gtest.h>

#include <chrono>

#include "platform/resources/CPUTextureResourceLoaderWorker.h"
#include "platform/resources/CPUTextureHandle.h"

using namespace Platform::Resources;

static auto workload = [](const std::filesystem::path& path) -> CPUTextureHandle {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return CPUTextureHandle();
};

TEST(CPUTextureLoadWorker, Init)
{
    // Note: Maybe it will be a better design to pass the workload 
    // on calling load()...that way we can have different workloads...
    // Idk if this is applicable, lets see in practice.
    CPUTextureLoadWorker loader(workload);

    EXPECT_TRUE(&loader);
}

TEST(CPUTextureLoadWorker, Load)
{
    CPUTextureLoadWorker loader(workload);
    const std::string path = std::string(TEST_RESOURCE_DIR) + "/Bishop_W.png";

    auto start = std::chrono::steady_clock::now();
    const auto idOrErr = loader.load(path);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Loading texture took: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    EXPECT_TRUE(idOrErr.has_value());
    auto id = idOrErr.value();

    // This test is kinda heavy too ....
    // maybe there is a way to make the is valid check have a cheap way to wait?
    while (!loader.isValid(id)) {
    }

    EXPECT_TRUE(loader.isValid(id));
}

TEST(CPUTextureLoadWorker, LoadTwo)
{
    CPUTextureLoadWorker loader(workload);
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

    while (loader.isValid(id1) == false || loader.isValid(id2) == false) {
    }

    EXPECT_TRUE(loader.isValid(id1));
    EXPECT_TRUE(loader.isValid(id2));
}