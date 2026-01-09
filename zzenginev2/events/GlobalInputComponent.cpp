#include <cstdlib>
#include <iostream>

#include "SDL_events.h"

#include "GlobalInputComponent.h"
#include "enginev2/debug/Debug.h"

int32_t GlobalInputComponent::init() {
	sdlEvent = new SDL_Event { }; // Calling with "zero initializer" {}

	if (sdlEvent == nullptr) {
		DebugLog.showErrorInfo("Bad allocation of SDL_Event");
		std::cerr << "Bad allocation of SDL_Event" << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void GlobalInputComponent::deinit() {
	if (sdlEvent != nullptr) {
		delete sdlEvent;
		sdlEvent = nullptr;
	}
}

bool GlobalInputComponent::poll() {
	if (SDL_PollEvent(sdlEvent) == 0) {
		return false;
	}

	SDL_GetMouseState(&posX, &posY);
	setEventTypeInternal();

	return true;
}

bool GlobalInputComponent::hasExitEvent() const {
	return sdlEvent->type == EventType::QUIT;
}

bool GlobalInputComponent::isKeyPressed(int32_t keyCode)
{
	return isKeyPressedMap[keyCode];
}

void GlobalInputComponent::setEventTypeInternal() {
	switch (sdlEvent->type) {
	case EventType::KEYBOARD_PRESS:
		mouseButton = Mouse::UNKNOWN;
		touchEvent = TouchEvent::KEYBOARD_PRESS;
		isKeyPressedMap[sdlEvent->key.keysym.sym] = true;
		break;

	case EventType::KEYBOARD_RELEASE:
		mouseButton = Mouse::UNKNOWN;
		touchEvent = TouchEvent::KEYBOARD_RELEASE;
		isKeyPressedMap[sdlEvent->key.keysym.sym] = false;
		break;

	case EventType::MOUSE_PRESS:
		mouseButton = sdlEvent->button.button;
		touchEvent = TouchEvent::UNKNOWN;
		break;
	case EventType::FINGER_PRESS:
		mouseButton = Mouse::UNKNOWN;
		touchEvent = TouchEvent::TOUCH_PRESS;
		break;

	case EventType::MOUSE_RELEASE:
		mouseButton = sdlEvent->button.button;
		touchEvent = TouchEvent::UNKNOWN;
		break;
	case EventType::FINGER_RELEASE:
		mouseButton = Mouse::UNKNOWN;
		touchEvent = TouchEvent::TOUCH_RELEASE;
		break;

		//X is pressed on the window (or CTRL-C signal is sent)
	case EventType::QUIT:
	default:
		mouseButton = Mouse::UNKNOWN;
		touchEvent = TouchEvent::UNKNOWN;
		break;
	}
}
