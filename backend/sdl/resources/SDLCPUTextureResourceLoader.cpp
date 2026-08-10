#include "SDLCPUTextureResourceLoader.h"

#include <filesystem>

#include "SDLCPUTexture.h"
#include "SDLResourceUtils.h"

#include "SDL_image.h"
#include "backend/sdl/error/SDLError.h"

using namespace Backend::SDL::Resources;
using namespace Platform::Resources;
using namespace Core::Errors;

namespace {
const LoadTextureFunc loadSDLTex = [](const std::filesystem::path& path) -> std::expected<TextureHandle, ErrorCode> {
	const std::filesystem::path finalPath = resolvePath(path);
	SDL_Surface* loadedSurface = IMG_Load((const char*)(finalPath.u8string().c_str()));

	if (!loadedSurface) return std::unexpected(Backend::SDL::Error::make(ANGINA_CURRENT_FUNCTION));

	return TextureHandle(new SDLCPUTexture(loadedSurface));
};
}

SDLCPUTextureResourceLoader::SDLCPUTextureResourceLoader():
	AsyncTextureLoadWorker(loadSDLTex) {}

std::unique_ptr<SDLCPUTextureResourceLoader> SDLCPUTextureResourceLoader::make()
{
	return std::make_unique<SDLCPUTextureResourceLoader>();
}
