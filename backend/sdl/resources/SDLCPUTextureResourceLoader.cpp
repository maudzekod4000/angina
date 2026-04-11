#include "SDLCPUTextureResourceLoader.h"

#include <filesystem>

#include "SDLCPUTexture.h"

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Platform::Resources;
using namespace Core::Errors;

namespace {
const LoadTextureFunc loadSDLTex = [](const std::filesystem::path& path) -> std::expected<CPUTextureHandle, ErrorCode> {
	CPUTextureHandle loadedTexHandle{};

	SDL_Surface* loadedSurface = IMG_Load((const char*)(path.u8string().c_str()));

	if (!loadedSurface) return std::unexpected(ErrorCode(-1, "Failed to load surface."));

	loadedTexHandle.ptr = new SDLCPUTexture(loadedSurface);
	loadedTexHandle.isReady = true;

	return loadedTexHandle;
};
}

SDLCPUTextureResourceLoader::SDLCPUTextureResourceLoader():
	CPUTextureLoadWorker(loadSDLTex) {}

std::unique_ptr<SDLCPUTextureResourceLoader> SDLCPUTextureResourceLoader::make()
{
	return std::make_unique<SDLCPUTextureResourceLoader>();
}
