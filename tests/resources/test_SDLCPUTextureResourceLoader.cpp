#include <gtest/gtest.h>

#include <string>

#include "backend/sdl/resources/SDLCPUTextureResourceLoader.h"

using namespace Backend::SDL::Resources;

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

    EXPECT_FALSE(idOrErr.has_value());
}
