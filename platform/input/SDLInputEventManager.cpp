#include "SDLInputEventManager.h"

using namespace Angina::Errors;
using namespace Angina::Input;
using namespace Angina::Units;

#include "SDL_events.h"

SDLInputEventManager::SDLInputEventManager(InputRefreshRate r): BaseInputEventManager(r) {}

std::unique_ptr<SDLInputEventManager> Angina::Input::SDLInputEventManager::make(InputRefreshRate r)
{
	return std::unique_ptr<SDLInputEventManager>(new SDLInputEventManager(r));
}

std::expected<void, ErrorCode> SDLInputEventManager::onWorkTick()
{
	SDL_Event e{};

	if (SDL_PollEvent(&e) == 0) {
		return std::expected<void, ErrorCode>();
	}

	// Note: Its a bit wasteful to send a whole object for a single polled event...
	// Maybe instead of having setSnapshot, we can have setters...but thats going to grow fast...
	// I suppose this is the common trade-off between maintenance and performance... :) Whatdoyoudo...
	const InputSnapshot evSnap = mapEvent(e);
	setSnapshot(evSnap);

	return std::expected<void, ErrorCode>();
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
