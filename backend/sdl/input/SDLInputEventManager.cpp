#include "SDLInputEventManager.h"

using namespace Core::Errors;
using namespace Platform::Input;
using namespace Platform::System;
using namespace Backend::SDL::Input;

#include "SDL_events.h"

SDLInputEventManager::SDLInputEventManager(): BaseInputEventManager() {}

std::unique_ptr<SDLInputEventManager> SDLInputEventManager::make()
{
	return std::unique_ptr<SDLInputEventManager>(new SDLInputEventManager());
}

ErrorCode SDLInputEventManager::update(Phase phase)
{
	if (phase != Phase::Input) return ErrorCode();

	SDL_Event e{};
	InputSnapshot inEvent;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EventType::SDL_QUIT:
			inEvent.quit = true;
			break;
		}
	}

	setSnapshot(inEvent);

	return ErrorCode();
}
