#include "SDLVideoLifecycleManager.h"

#include "backend/sdl/error/SDLError.h"

#include <SDL.h>

using namespace Core::Errors;
using namespace Backend::SDL::Init;

ErrorCode SDLVideoLifecycleManager::init(uint64_t flags)
{
	if (const int res = SDL_Init(SDL_INIT_VIDEO); res != 0) {
		return Error::make(ANGINA_CURRENT_FUNCTION);
	}

	return ErrorCode();
}


ErrorCode SDLVideoLifecycleManager::destroy()
{
	SDL_Quit();
	return {};
}

bool SDLVideoLifecycleManager::isCriticalSubsystem()
{
	return true;
}
