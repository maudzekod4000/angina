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

	SDLCPUTexture* loadedCpuTex = new SDLCPUTexture(loadedSurface); // This class could clear the surface.
	CPUTextureHandle loadedTexHandle{};
	loadedTexHandle.ptr = loadedCpuTex; // This could be a unique_ptr
	loadedTexHandle.isReady = true;

	const Id texId = idGenerator.next();
	textureHandlesIndex[texId] = loadedTexHandle;

	return texId;
}
