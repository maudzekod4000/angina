#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <filesystem>

#include "helpers/file.h"

#include "platform/resources/GPUTextureLoader.h"

using namespace Platform::Resources;
using namespace Test::Helpers::File;
using namespace Core::Errors;

class MockTextureTransferer : public TextureTransferer {
public:
    std::expected<GPUTextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(CPUTextureHandle cpuHdl) override {
        GPUTextureHandle gpuHdl{};
        gpuHdl.ptr = tex;
        gpuHdl.isReady = true;
        return gpuHdl;
    }

private:
    GPUTexture* tex = new GPUTexture();
};

class MockCPULoader : public TextureResourceLoader<CPUTextureHandle> {
public:
    IdOrError load(const std::filesystem::path& resourceFile) override {
        return {};
    }

    std::vector<IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override {
        std::vector<IdOrError> res;
        res.push_back(1);
        res.push_back(std::unexpected(ErrorCode(-1, "This is an error...")));
        return res;
    }

    Core::Errors::ErrorCode release(Core::Identity::Id id) override {
        return ErrorCode();
    }

    CPUTextureHandle resolve(Core::Identity::Id id) override {
        CPUTextureHandle handle{};
        handle.ptr = fakeCpuTex;
        handle.isReady = true;
        return handle;
    }

    bool isValid(Core::Identity::Id id) override {
        return true;
    }

    bool isDone() const override {
        return true;
    }

    void wait() override {}

private:
    CPUTexture* fakeCpuTex = new CPUTexture();
};

TEST(GPUTextureLoader, Init)
{
    MockTextureTransferer myTransferer;
    MockCPULoader loader;
    GPUTextureLoader texLoader(&myTransferer, &loader);

    EXPECT_TRUE(&texLoader);
}

TEST(GPUTextureLoader, Load)
{
    MockTextureTransferer myTransferer;
    MockCPULoader loader;
    GPUTextureLoader texLoader(&myTransferer, &loader);

    const std::vector<std::filesystem::path> texFilePaths = {
        "a", "b"
    };

    auto idsOrErrs = texLoader.load(texFilePaths);

    ASSERT_EQ(texFilePaths.size(), idsOrErrs.size());

    auto someIdOrErr = idsOrErrs[0];

    ASSERT_TRUE(someIdOrErr.has_value());

    auto id = someIdOrErr.value();

    ASSERT_TRUE(texLoader.isValid(id));

    auto texHdl = texLoader.resolve(id);

    ASSERT_TRUE(texHdl.ptr != nullptr);
}
