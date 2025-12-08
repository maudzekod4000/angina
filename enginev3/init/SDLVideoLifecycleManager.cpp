#include "SDLVideoLifecycleManager.h"

#include <SDL.h>

using namespace Angina::Init;
using namespace Angina::Errors;

std::expected<void, ErrorCode> SDLVideoLifecycleManager::init(uint64_t flags)
{
	if (const int res = SDL_Init(SDL_INIT_VIDEO); res != 0) {
		return std::unexpected(ErrorCode(res, SDL_GetError()));
	}

	return;
}

std::expected<void, ErrorCode> SDLVideoLifecycleManager::destroy()
{
	SDL_Quit();
	return;
}
