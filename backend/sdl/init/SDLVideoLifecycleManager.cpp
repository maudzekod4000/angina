#include "SDLVideoLifecycleManager.h"

#include "backend/sdl/error/SDLError.h"

#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_image.h"

using namespace Core::Errors;
using namespace Backend::SDL::Error;

// TODO: Idk if we need separate methods for like video and audio and
// other subsystems.
ErrorCode Backend::SDL::Init::initSDLSystems(uint64_t flags)
{
	if (const int res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); res != 0) {
		return makeErr(ANGINA_CURRENT_FUNCTION);
	}

	//Initialize SDL_mixer
    if( Mix_OpenAudio( 44100 /* audio sampling rate */, MIX_DEFAULT_FORMAT, 2, 2048 /* how much to read at a time */) < 0)
    {
        return makeErr(ANGINA_CURRENT_FUNCTION);
    }

	return ErrorCode();
}

void Backend::SDL::Init::destroySDLSystems()
{
	SDL_Quit();
}
