#ifndef INIT_SDL_INITIALIZER_H
#define INIT_SDL_INITIALIZER_H

#include "core/error/Errors.h"

namespace Backend::SDL::Init {
	Core::Errors::ErrorCode initSDLSystems(uint64_t flags);
	void destroySDLSystems();
}

#endif // !INIT_SDL_INITIALIZER_H
