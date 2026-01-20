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

	const Id texId = idGenerator.next();
	
	//1. Do we have a free index in the freeList?

	//1.1 If there is a free index, use it to insert the new element in that slot

	//1.2 When there is no free index push to the end of the storage

	//2. After we have inserted that element in the storage use the index to add to the mapping.


	return texId;
}

ErrorCode SDLCPUTextureResourceLoader::release(Core::Identity::Id id)
{
	CPUTextureHandle handle = textureHandlesIndex[id];
	textureHandlesIndex.erase(id);
	delete handle.ptr;

	return ErrorCode();
}

CPUTextureHandle SDLCPUTextureResourceLoader::resolve(Core::Identity::Id id)
{
	return textureHandlesIndex[id];
}

bool SDLCPUTextureResourceLoader::isValid(Core::Identity::Id id)
{
	return textureHandlesIndex.find(id) != textureHandlesIndex.end();
}
