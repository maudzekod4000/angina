#ifndef BACKEND_SDL_SDL_RESOURCE_UTILS_H
#define BACKEND_SDL_SDL_RESOURCE_UTILS_H

#include <filesystem>

namespace Backend::SDL::Resources {

// Resolves a resource-relative path against the directory the executable lives
// in (as reported by SDL_GetBasePath), so resources are found regardless of the
// process's current working directory.
std::filesystem::path resolvePath(const std::filesystem::path& relativePath);

}

#endif // !BACKEND_SDL_SDL_RESOURCE_UTILS_H
