#include "SDLInputEventManager.h"

using namespace Core::Errors;
using namespace Platform::Input;
using namespace Platform::System;
using namespace Backend::SDL::Input;

#include "SDL_events.h"
#include "SDL_mouse.h"

void SDLInputEventManager::update()
{
	SDL_Event e{};

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EventType::SDL_QUIT:
			inEvent.quit = true;
			break;
		case SDL_EventType::SDL_MOUSEBUTTONUP:
			handleMouseClick();
			break;
		}
	}

	return;
}

void SDLInputEventManager::handleMouseClick()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	bool changed = x != inEvent.mouseX || y != inEvent.mouseY;

	if (changed && onClickHandler) {
		onClickHandler(x, y);
	}

	inEvent.mouseX = x;
	inEvent.mouseY = y;
}
