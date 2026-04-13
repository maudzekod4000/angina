#include "GPUTextureLoader.h"
#include "GPUTextureLoader.h"

using namespace Platform::Resources;

GPUTextureLoader::GPUTextureLoader(TextureTransferer* texTransferer) :
	texTransferer(texTransferer) {}

std::vector<IdOrError> GPUTextureLoader::load(const std::vector<std::filesystem::path>& resourceFiles)
{
	// Ok, so what do we do here...
	
	// 1. Use the CPU Loader to load the textures to main memory.
	auto ids = cpuTexLoader->load(resourceFiles);
	
	// 2. Wait for all the textures to load using the wait method
	cpuTexLoader->wait();

	std::vector<IdOrError> res;

	// 3. Transfer the textures to the GPU using the transfer class of your choice.
	for (auto idOrErr : ids) {
		if (idOrErr.has_value()) {
			auto id = idOrErr.value();

			if (cpuTexLoader->isValid(id)) {
				CPUTextureHandle cpuHandle = cpuTexLoader->resolve(id);
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


