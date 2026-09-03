#ifndef BACKEND_SDL_RESOURCES_LOADER_H
#define BACKEND_SDL_RESOURCES_LOADER_H

#include "core/error/Errors.h"

#include "SDLTexture.h"

struct SDL_Renderer;

namespace Backend::SDL::Resources {
	SDLTexture load(const char* filepath, SDL_Renderer*, Core::Errors::ErrorCode&);
}

#endif // !BACKEND_SDL_RESOURCES_LOADER_H
