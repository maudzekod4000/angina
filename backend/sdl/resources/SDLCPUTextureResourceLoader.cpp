#include "SDLCPUTextureResourceLoader.h"

#include <filesystem>

#include "SDLCPUTexture.h"

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Platform::Resources;

namespace {
const auto loadSDLTex = [](const std::filesystem::path& path) -> CPUTextureHandle {
	CPUTextureHandle loadedTexHandle{};

	SDL_Surface* loadedSurface = IMG_Load((const char*)(path.u8string().c_str()));

	if (!loadedSurface) return loadedTexHandle;

	loadedTexHandle.ptr = new SDLCPUTexture(loadedSurface);
	loadedTexHandle.isReady = true;

	return loadedTexHandle;
};
}

SDLCPUTextureResourceLoader::SDLCPUTextureResourceLoader():
	CPUTextureLoadWorker(loadSDLTex) {}
