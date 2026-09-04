#include "SDLVideoLifecycleManager.h"

#include "backend/sdl/error/SDLError.h"

#include <SDL.h>

using namespace Core::Errors;
using namespace Backend::SDL::Init;
using namespace Backend::SDL::Error;

// TODO: Idk if we need separate methods for like video and audio and
// other subsystems.
ErrorCode initVideo(uint64_t flags)
{
	if (const int res = SDL_Init(SDL_INIT_VIDEO); res != 0) {
		return makeErr(ANGINA_CURRENT_FUNCTION);
	}

	return ErrorCode();
}


void destroyVideo()
{
	SDL_Quit();
}
