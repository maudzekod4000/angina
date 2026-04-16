#include <gtest/gtest.h>

#include "platform/resources/GPUTextureLoader.h"

using namespace Platform::Resources;

GPUTexture tex{};

class MyTextureTransferer : public TextureTransferer {
public:
    std::expected<GPUTextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(CPUTextureHandle cpuHdl) override {
        GPUTextureHandle gpuHdl{};
        gpuHdl.ptr = &tex;
        gpuHdl.isReady = true;
        return gpuHdl;
    }
};

TEST(GPUTextureLoader, Init)
{
    MyTextureTransferer myTransferer;
    GPUTextureLoader texLoader(&myTransferer);

    EXPECT_TRUE(&texLoader);
}
