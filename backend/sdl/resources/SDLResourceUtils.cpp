#include "SDLResourceUtils.h"

#include "SDL.h"

namespace Backend::SDL::Resources {

std::filesystem::path resolvePath(const std::filesystem::path& relativePath) {
	// Cached for the whole duration of the program. SDL_GetBasePath allocates in
	// SDL2, but this pointer is intentionally never freed: we need it until exit.
	static const char* basePath = SDL_GetBasePath();

	if (!basePath) return relativePath;

	return std::filesystem::path(basePath) / relativePath;
}

}
