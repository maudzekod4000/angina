#include "SDLCPUTextureResourceLoaderAsync.h"

#include <future>
#include <chrono>
#include <vector>

#include "backend/sdl/resources/SDLCPUTexture.h"

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Core::Identity;
using namespace Core::Errors;
using namespace Platform::Resources;

IdOrError SDLCPUTextureLoaderAsync::load(const std::filesystem::path& resourceFile)
{
	return IdOrError();
}

std::vector<IdOrError> SDLCPUTextureLoaderAsync::load(const std::vector<std::filesystem::path>& resourceFiles)
{
	std::vector<std::future<SDL_Surface*>> surfacesFut;
	surfacesFut.reserve(resourceFiles.size());

	for (const auto& file : resourceFiles) {
		surfacesFut.push_back(std::async(std::launch::async, [file]() -> SDL_Surface* {
			return IMG_Load((const char*)(file.u8string().c_str()));
		}));
	}

	std::vector<IdOrError> result;
	result.reserve(resourceFiles.size());

	for (auto& fut : surfacesFut) {
		SDL_Surface* surface = fut.get();

		if (surface) {
			CPUTextureHandle loadedTexHandle{};
			loadedTexHandle.ptr = new SDLCPUTexture(surface);
			loadedTexHandle.isReady = true;

			const Id texId = texHandleFreeList.add(loadedTexHandle);

			result.push_back(texId);
		}
		else {
			result.push_back(std::unexpected(ErrorCode(-1, "Failed to load surface.")));
		}
	}

	return result;
}

ErrorCode SDLCPUTextureLoaderAsync::release(Core::Identity::Id id)
{
	texHandleFreeList.remove(id);
	return ErrorCode();
}

CPUTextureHandle SDLCPUTextureLoaderAsync::resolve(Core::Identity::Id id)
{
	return texHandleFreeList.get(id);
}

bool SDLCPUTextureLoaderAsync::isValid(Core::Identity::Id id)
{
	return texHandleFreeList.has(id);
}
