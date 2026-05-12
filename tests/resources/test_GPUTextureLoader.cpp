#include <gtest/gtest.h>

#include <vector>
#include <filesystem>
#include <memory>

#include "platform/resources/TextureTransferer.h"
#include "platform/resources/TextureResourceLoader.h"
#include "platform/resources/GPUTextureLoader.h"

using namespace Platform::Resources;
using namespace Core::Errors;

class MockTextureTransferer : public TextureTransferer {
public:
    std::expected<TextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(TextureHandle cpuHdl) override {
        return TextureHandle(tex.get());
    }

private:
    std::unique_ptr<Texture> tex = std::make_unique<Texture>();
};

class MockCPULoader : public TextureResourceLoader<TextureHandle> {
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

    TextureHandle resolve(Core::Identity::Id id) override {
        return TextureHandle(fakeCpuTex.get());
    }

    bool isValid(Core::Identity::Id id) override {
        return true;
    }

    bool isDone() const override {
        return true;
    }

    void wait() override {}

private:
    std::unique_ptr<Texture> fakeCpuTex = std::make_unique<Texture>();
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
