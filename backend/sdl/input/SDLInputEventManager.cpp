#include "SDLInputEventManager.h"

using namespace Core::Errors;
using namespace Platform::Input;
using namespace Backend::SDL::Input;

#include "SDL_events.h"

SDLInputEventManager::SDLInputEventManager(): BaseInputEventManager() {}

std::unique_ptr<SDLInputEventManager> SDLInputEventManager::make()
{
	return std::unique_ptr<SDLInputEventManager>(new SDLInputEventManager());
}

ErrorCode SDLInputEventManager::update()
{
	SDL_Event e{};

	while (SDL_PollEvent(&e)) {
		// Note: Its a bit wasteful to send a whole object for a single polled event...
		// Maybe instead of having setSnapshot, we can have setters...but thats going to grow fast...
		// I suppose this is the common trade-off between maintenance and performance... :) Whatdoyoudo...
		const InputSnapshot evSnap = mapEvent(e);
		setSnapshot(evSnap);
	}

	return ErrorCode();
}

InputSnapshot SDLInputEventManager::mapEvent(SDL_Event e)
{
	InputSnapshot inEvent;

	switch (e.type) {
	case SDL_EventType::SDL_QUIT:
		inEvent.quit = true;
		break;
	}

	return inEvent;
}
