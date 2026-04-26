#include "GPUTextureLoader.h"

#include <memory>

using namespace Platform::Resources;

GPUTextureLoader::GPUTextureLoader(TextureTransferer* texTransferer, TextureResourceLoader<CPUTextureHandle>* cpuTexLoader) :
	texTransferer(texTransferer), cpuTexLoaderPtr(cpuTexLoader) {}

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
				CPUTextureHandle cpuHandle = cpuTexLoaderPtr->resolve(id);
				auto gpuHandleOrErr = texTransferer->convertCPUToGPUTexture(cpuHandle);

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


