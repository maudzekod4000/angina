#ifndef BACKEND_SDL_RESOURCES_LOADER_H
#define BACKEND_SDL_RESOURCES_LOADER_H

#include "core/error/Errors.h"

#include "SDLTexture.h"

namespace Backend::SDL::Resources {
	SDLTexture load(const char* filepath, Core::Errors::ErrorCode& outErr);
}

#endif // !BACKEND_SDL_RESOURCES_LOADER_H
