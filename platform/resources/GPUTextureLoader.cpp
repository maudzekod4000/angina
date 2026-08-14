#include "GPUTextureLoader.h"

#include <memory>

using namespace Platform::Resources;
using namespace Core::Errors;

GPUTextureLoader::GPUTextureLoader(std::shared_ptr<TextureTransferer> texTransferer, std::unique_ptr<TextureResourceLoader> cpuTexLoader) :
	texTransfererPtr(std::move(texTransferer)), cpuTexLoaderPtr(std::move(cpuTexLoader)) {}

std::vector<IdOrError> GPUTextureLoader::load(const std::vector<std::filesystem::path>& resourceFiles)
{
	auto ids = cpuTexLoaderPtr->load(resourceFiles);
	
	cpuTexLoaderPtr->wait();

	// Note: Whoa....std::expected is 72 bytes...
	// I don't think i use it in some hot paths but its worth keeping in mind.
	std::vector<IdOrError> res;

	for (const auto& idOrErr : ids) {
		if (!idOrErr || cpuTexLoaderPtr->hasError(idOrErr.value())) {
			res.push_back(std::unexpected(idOrErr.error()));
			continue;
		}

		TextureHandle cpuHandle = cpuTexLoaderPtr->resolve(idOrErr.value());
		auto gpuHandleOrErr = texTransfererPtr->transferGPU(cpuHandle);

		if (!gpuHandleOrErr) {
			res.push_back(std::unexpected(gpuHandleOrErr.error()));
			continue;
		}

		auto gpuId = gpuTexturesFreeList.add(gpuHandleOrErr.value());
		res.push_back(gpuId);
	}

	return res;
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
