#include "GPUTextureLoader.h"

#include <memory>

using namespace Platform::Resources;
using namespace Core::Errors;

GPUTextureLoader::GPUTextureLoader(std::shared_ptr<TextureTransferer> texTransferer, std::unique_ptr<TextureResourceLoader<TextureHandle>> cpuTexLoader) :
	texTransfererPtr(std::move(texTransferer)), cpuTexLoaderPtr(std::move(cpuTexLoader)) {}

std::vector<IdOrError> GPUTextureLoader::load(const std::vector<std::filesystem::path>& resourceFiles)
{
	// Ok, so what do we do here...
	
	// 1. Use the CPU Loader to load the textures to main memory.
	auto ids = cpuTexLoaderPtr->load(resourceFiles);
	
	// 2. Wait for all the textures to load using the wait method
	cpuTexLoaderPtr->wait();

	std::vector<IdOrError> res;

	// 3. Transfer the textures to the GPU using the transfer class of your choice.
	for (auto idOrErr : ids) {
		if (idOrErr.has_value()) {
			auto id = idOrErr.value();

			if (cpuTexLoaderPtr->isValid(id)) {
				TextureHandle cpuHandle = cpuTexLoaderPtr->resolve(id);
				auto gpuHandleOrErr = texTransfererPtr->convertCPUToGPUTexture(cpuHandle);

				if (gpuHandleOrErr.has_value()) {
					auto addId = gpuTexturesFreeList.add(gpuHandleOrErr.value());
					res.push_back(addId);
				}
				else {
					res.push_back(std::unexpected(gpuHandleOrErr.error()));
				}
			}
		}
		else {
			// Relay the error to the caller.
			res.push_back(std::unexpected(idOrErr.error()));
		}
	}
	// 4. This will be a synchrnonous task so, just return...
	return res; // Actually, we can test this with a test...i dont see a problem.
}

IdOrError GPUTextureLoader::load(const std::filesystem::path& resourceFile)
{
	return {};
}

ErrorCode GPUTextureLoader::release(Core::Identity::Id id)
{
	gpuTexturesFreeList.remove(id);
	return ErrorCode();
}

TextureHandle GPUTextureLoader::resolve(Core::Identity::Id id)
{
	return gpuTexturesFreeList.get(id);
}

bool GPUTextureLoader::isValid(Core::Identity::Id id)
{
	return gpuTexturesFreeList.has(id);
}

bool GPUTextureLoader::isDone() const
{
	return true;
}

void GPUTextureLoader::wait()
{
	return;
}
