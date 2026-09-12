#include "SDLInputEventManager.h"

using namespace Core::Errors;
using namespace Platform::Input;
using namespace Platform::System;
using namespace Backend::SDL::Input;

#include "SDL_events.h"

void SDLInputEventManager::update(Phase phase)
{
	if (phase != Phase::Input) return;

	SDL_Event e{};

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EventType::SDL_QUIT:
			inEvent.quit = true;
			break;
		}
	}

	return;
}
