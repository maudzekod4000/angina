#include "GPUTextureLoader.h"

#include <memory>

using namespace Platform::Resources;
using namespace Core::Errors;

GPUTextureLoader::GPUTextureLoader(std::shared_ptr<TextureTransferer> texTransferer, std::unique_ptr<TextureResourceLoader> cpuTexLoader) :
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

			// TODO: we can check hasError as a first thing of this loop
			// ids will always contain just values because it's an async api
			// only after wait() we can check with hasError, whether something is
			// success.
			const ErrorCode cpuLoadErr = cpuTexLoaderPtr->hasError(id);
			if (!cpuLoadErr) {
				TextureHandle cpuHandle = cpuTexLoaderPtr->resolve(id);
				auto gpuHandleOrErr = texTransfererPtr->transferGPU(cpuHandle);

				if (gpuHandleOrErr.has_value()) {
					auto addId = gpuTexturesFreeList.add(gpuHandleOrErr.value());
					res.push_back(addId);
				}
				else {
					res.push_back(std::unexpected(gpuHandleOrErr.error()));
				}
			}
			else {
				res.push_back(std::unexpected(cpuLoadErr));
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
	auto results = load(std::vector<std::filesystem::path>{ resourceFile });
	return results[0];
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

ErrorCode GPUTextureLoader::hasError(Core::Identity::Id id)
{
	if (gpuTexturesFreeList.has(id)) return {};
	return ErrorCode(1, "Texture not found");
}

bool GPUTextureLoader::isDone() const
{
	return true;
}

void GPUTextureLoader::wait()
{
	return;
}
