#ifndef SDL_ENGINE_BUTTONS_BUTTONMANAGER_H_
#define SDL_ENGINE_BUTTONS_BUTTONMANAGER_H_

#include <vector>
#include <cstdint>

#include "platform/sdl/events/InputEvent.h"
#include "renderer/primitives/Point.h"
#include "renderer/utils/PrimitivesUtils.h"

class InputEvent;

/**
 * Holds reference to something that has position, dimensions and a callback and gets called to check whether it has been clicked.
 * TODO: This can be extended to support multiple event types and callbacks.
 */
template <typename T>
class EventManager {
public:
	~EventManager();
	void add(T& target) {
		targets.push_back(&target);
	}

	bool invokeCallback(const InputEvent& event) {
		if (event.type != EventType::MOUSE_RELEASE) {
			return false;
		}

		Point clickPoint = { static_cast<float>(event.posX), static_cast<float>(event.posY) };

		std::cout << "Clicked at " << clickPoint << std::endl;

		for (auto const &button : targets) {
			if (PrimitivesUtils::isInRect(button->getPosition(), button->getDimensions(), clickPoint)) {
				button->getCallback()();

				return true;
			}
		}

		return false;
	}

	void clear();
private:
	std::vector<T*> targets;
};

#endif /* SDL_ENGINE_BUTTONS_BUTTONMANAGER_H_ */
