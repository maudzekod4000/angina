#include "SDLCPUTextureResourceLoader.h"

#include <cassert>

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Core::Identity;
using namespace Core::Errors;
using namespace Platform::Resources;

IdOrError SDLCPUTextureResourceLoader::load(const std::filesystem::path& resourceFile)
{
	assert(!resourceFile.empty());

	SDL_Surface* loadedSurface = IMG_Load((const char*)(resourceFile.u8string().c_str()));

	if (!loadedSurface) {
		// TODO: SDL provides ways to query the system for errors and get a more concrete error msg.
		return std::unexpected(ErrorCode(-1, "Failed to load surface."));
	}

	CPUTextureHandle loadedTexHandle{};
	loadedTexHandle.ptr = new SDLCPUTexture(loadedSurface);
	loadedTexHandle.isReady = true; // Loading surfaces sync right now.

	const Id texId = texHandleFreeList.add(loadedTexHandle);

	return texId;
}

ErrorCode SDLCPUTextureResourceLoader::release(Core::Identity::Id id)
{	
	texHandleFreeList.remove(id);

	return ErrorCode();
}

CPUTextureHandle SDLCPUTextureResourceLoader::resolve(Core::Identity::Id id)
{
	return texHandleFreeList.get(id);
}

bool SDLCPUTextureResourceLoader::isValid(Core::Identity::Id id)
{
	return texHandleFreeList.has(id);
}
