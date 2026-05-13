#ifndef PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H
#define PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H

#include <memory>

#include "platform/resources/TextureResourceLoader.h"
#include "platform/resources/TextureHandle.h"
#include "platform/resources/TextureTransferer.h"
#include "core/datastructures/FreeList.h"

namespace Platform::Resources {

/// Loads resources first to main memory and then to the GPU.
/// Depending on the transferer and the graphics API, this class might need to
/// be called from the main thread.
class GPUTextureLoader : public TextureResourceLoader {
public:
	explicit GPUTextureLoader(std::shared_ptr<TextureTransferer>, std::unique_ptr<TextureResourceLoader>);

	IdOrError load(const std::filesystem::path& resourceFile) override;

	std::vector<IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	TextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;

	bool isDone() const override;

	void wait() override;

private:
	std::unique_ptr<TextureResourceLoader> cpuTexLoaderPtr;
	std::shared_ptr<TextureTransferer> texTransfererPtr;
	Core::DataStructures::FreeList<TextureHandle> gpuTexturesFreeList;
};

using GPUTextureLoaderPtr = std::unique_ptr<GPUTextureLoader>;

}

#endif // !PLATFORM_RESOURCES_GPU_TEXTURE_LOADER_H
