#ifndef PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H
#define PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H

#include "platform/resources/CPUTextureResourceLoader.h"
#include "platform/resources/GPUTextureHandle.h"
#include "platform/resources/TextureTransferer.h"
#include "core/datastructures/FreeList.h"

namespace Platform::Resources {
class GPUTextureLoader : public CPUTextureResourceLoader<GPUTextureHandle> {
public:
	explicit GPUTextureLoader(TextureTransferer* texTransferer);

	IdOrError load(const std::filesystem::path& resourceFile) override {
		return {};
	}

	std::vector<IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override {
		return Core::Errors::ErrorCode();
	}

	GPUTextureHandle resolve(Core::Identity::Id id) override {
		return GPUTextureHandle{};
	}

	bool isValid(Core::Identity::Id id) override {
		return false;
	}

	bool isDone() const override {
		return false;
	}

	void wait() override {}

private:
	CPUTextureResourceLoaderPtr cpuTexLoader;
	TextureTransferer* texTransferer = nullptr;
	Core::DataStructures::FreeList<GPUTextureHandle> gpuTexturesFreeList;
};
}

#endif // !PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H
