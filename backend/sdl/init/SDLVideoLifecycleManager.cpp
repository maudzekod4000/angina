#include "SDLVideoLifecycleManager.h"

#include <SDL.h>

using namespace Angina::Init;
using namespace Angina::Errors;

ErrorCode SDLVideoLifecycleManager::init(uint64_t flags)
{
	if (const int res = SDL_Init(SDL_INIT_VIDEO); res != 0) {
		return ErrorCode(res, SDL_GetError());
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
