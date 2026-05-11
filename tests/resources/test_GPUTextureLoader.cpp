#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <filesystem>
#include <memory>

#include "platform/resources/GPUTextureLoader.h"

using namespace Platform::Resources;
using namespace Core::Errors;

class MockTextureTransferer : public TextureTransferer {
public:
    std::expected<GPUTextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(CPUTextureHandle cpuHdl) override {
        GPUTextureHandle gpuHdl{};
        gpuHdl.ptr = tex.get();
        gpuHdl.isReady = true;
        return gpuHdl;
    }

private:
    std::unique_ptr<GPUTexture> tex = std::make_unique<GPUTexture>();
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
        handle.ptr = fakeCpuTex.get();
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
    std::unique_ptr<CPUTexture> fakeCpuTex = std::make_unique<CPUTexture>();
};

TEST(GPUTextureLoader, Init)
{
    auto transferer = std::make_shared<MockTextureTransferer>();
    auto loader = std::make_unique<MockCPULoader>();
    GPUTextureLoader texLoader(std::move(transferer), std::move(loader));

    EXPECT_TRUE(&texLoader);
}

TEST(GPUTextureLoader, Load)
{
    auto transferer = std::make_shared<MockTextureTransferer>();
    auto loader = std::make_unique<MockCPULoader>();
    GPUTextureLoader texLoader(std::move(transferer), std::move(loader));

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
