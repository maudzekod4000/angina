#include <gtest/gtest.h>

#include <chrono>

#include "platform/resources/CPUTextureResourceLoaderWorker.h"
#include "platform/resources/TextureHandle.h"

#include "helpers/file.h"

using namespace Platform::Resources;
using namespace Test::Helpers::File;

static auto workload = [](const std::filesystem::path& path) -> TextureHandle {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return TextureHandle(nullptr);
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
    const auto path = resource("Bishop_W.png");

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
    const auto path1 = resource("Bishop_W.png");
    const auto path2 = resource("Bishop_B.png");
    
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

TEST(CPUTextureLoadWorker, LoadManyResolveOne)
{
    const auto dir = resource("textures10");
    const std::vector<std::filesystem::path> texFilePaths = loadFileNames(dir);

    std::vector<std::filesystem::path> texFilePaths50;
    texFilePaths50.reserve(texFilePaths.size() * 5);

    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());
    texFilePaths50.insert(texFilePaths50.begin(), texFilePaths.begin(), texFilePaths.end());

    EXPECT_EQ(50, texFilePaths50.size());

    CPUTextureLoadWorker loader(workload);

    auto start = std::chrono::steady_clock::now();
    const auto ids = loader.load(texFilePaths50);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Executing load method took: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<
        " ms." << std::endl;

    auto id = ids[20].value();

    // TODO: This is not cool, because some resources might just fail to load
    // and this will clog the whole test execution forever...
    while (!loader.isValid(id)) {
    }

    auto texLoadedEnd = std::chrono::steady_clock::now();
    std::cout << "Actually loading the textures took: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(texLoadedEnd - start).count() <<
        " ms." << std::endl;

    EXPECT_TRUE(loader.isValid(id));
}

/// This test is meant to be debugged and observed and has little value by
/// just being run.
TEST(CPUTextureLoadWorker, ThreadRelaxation)
{
    CPUTextureLoadWorker loader(workload);
    const auto path1 = resource("Bishop_W.png");
    const auto path2 = resource("Bishop_B.png");
    
    const auto id1 = loader.load(path1);

    // Wait for the texture to load
    while (!loader.isValid(id1.value())) {}

    // Observe that the loader is waiting via debugging.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    const auto id2 = loader.load(path2);

    // The loader should be back into working mode
    while (!loader.isValid(id2.value())) {}

    // Observe that the loader is waiting via debugging.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(CPUTextureLoadWorker, TypicalEngineUsage)
{
    CPUTextureLoadWorker loader(workload);
    const auto path1 = resource("Bishop_W.png");
    const auto path2 = resource("Bishop_B.png");
    
    const auto ids = loader.load(std::vector{ path1, path2 });
    // Usually around this point in code we will have more subsystems loading resources:
    // Audio, shaders, serialized maps or levels, etc.
    loader.wait();

    EXPECT_TRUE(loader.isValid(ids[0].value()));
    EXPECT_TRUE(loader.isValid(ids[1].value()));

    // Attepmting to load a second batch. The state of the class should be ready.
    const auto path3 = resource("Queen_B.png");
    const auto path4 = resource("Queen_W.png");
    const auto path5 = resource("Rook_B.png");

    const auto ids2 = loader.load(std::vector{ path3, path4, path5 });

    loader.wait();

    EXPECT_TRUE(loader.isValid(ids2[0].value()));
    EXPECT_TRUE(loader.isValid(ids2[1].value()));
    EXPECT_TRUE(loader.isValid(ids2[2].value()));
}
