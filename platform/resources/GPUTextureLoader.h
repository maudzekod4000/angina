#ifndef PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H
#define PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H

#include "platform/resources/TextureResourceLoader.h"
#include "platform/resources/GPUTextureHandle.h"
#include "platform/resources/TextureTransferer.h"
#include "core/datastructures/FreeList.h"

namespace Platform::Resources {
class GPUTextureLoader : public TextureResourceLoader<GPUTextureHandle> {
public:
	explicit GPUTextureLoader(TextureTransferer* texTransferer, TextureResourceLoader<CPUTextureHandle>*);

	IdOrError load(const std::filesystem::path& resourceFile) override {
		return {};
	}

	std::vector<IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override {
		return Core::Errors::ErrorCode();
	}

	GPUTextureHandle resolve(Core::Identity::Id id) override {
		return gpuTexturesFreeList.get(id);
	}

	bool isValid(Core::Identity::Id id) override {
		return gpuTexturesFreeList.has(id);
	}

	bool isDone() const override {
		return false;
	}

	void wait() override {}

private:
	TextureResourceLoader<CPUTextureHandle>* cpuTexLoaderPtr = nullptr; ///< Do not delete from this class' destructor.
	TextureTransferer* texTransferer = nullptr;
	Core::DataStructures::FreeList<GPUTextureHandle> gpuTexturesFreeList;
};
}

#endif // !PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H
