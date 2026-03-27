#include <gtest/gtest.h>

#include <string>
#include <filesystem>
#include <vector>

#include "backend/sdl/resources/SDLCPUTextureResourceLoaderHyperAsync.h"

using namespace Backend::SDL::Resources;

TEST(SDLCPUTextureResourceHyperAsync, Init)
{
    SDLCPUTextureLoaderHyperAsync loader;

    EXPECT_TRUE(&loader);
}
