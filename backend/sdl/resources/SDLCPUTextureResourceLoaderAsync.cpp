#include "SDLCPUTextureResourceLoaderAsync.h"

#include <future>
#include <chrono>
#include <vector>

#include "backend/sdl/resources/SDLCPUTexture.h"
#include "backend/sdl/error/SDLError.h"

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
			const Id texId = texHandleFreeList.add(TextureHandle(new SDLCPUTexture(surface)));

			result.push_back(texId);
		}
		else {
			result.push_back(std::unexpected(Error::make(ANGINA_CURRENT_FUNCTION)));
		}
	}

	return result;
}

ErrorCode SDLCPUTextureLoaderAsync::release(Core::Identity::Id id)
{
	texHandleFreeList.remove(id);
	return ErrorCode();
}

TextureHandle SDLCPUTextureLoaderAsync::resolve(Core::Identity::Id id)
{
	return texHandleFreeList.get(id);
}

ErrorCode SDLCPUTextureLoaderAsync::hasError(Core::Identity::Id id)
{
	if (texHandleFreeList.has(id)) return {};
	return ErrorCode(1, "Texture not found");
}

bool SDLCPUTextureLoaderAsync::isDone() const
{
	return true;
}

void SDLCPUTextureLoaderAsync::wait()
{
}
