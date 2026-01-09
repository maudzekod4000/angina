#ifndef SDLUTILS_INPUTEVENT_H_
#define SDLUTILS_INPUTEVENT_H_

#include <cstdint>
#include <unordered_map>

#include "platform/sdl/events/EventDefines.h"

union SDL_Event;

class GlobalInputComponent {
public:
	int32_t init();
	void deinit();
	bool poll();
	bool hasExitEvent() const;
	bool isKeyPressed(int32_t keyCode);

	int32_t posX;
	int32_t posY;
	int8_t mouseButton = Mouse::UNKNOWN;
	TouchEvent touchEvent = TouchEvent::UNKNOWN;
private:
	void setEventTypeInternal();

	SDL_Event *sdlEvent = nullptr;
	std::unordered_map<int32_t, bool> isKeyPressedMap;
};

#endif /* SDLUTILS_INPUTEVENT_H_ */
