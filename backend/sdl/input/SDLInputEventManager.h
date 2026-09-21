#ifndef PLATFORM_INPUT_EVENT_MANAGER_H
#define PLATFORM_INPUT_EVENT_MANAGER_H

#include <functional>

#include "platform/input/BaseInputEventManager.h"

namespace Backend::SDL::Input {

using OnClickHandler = std::function<void(int x, int y)>;

class SDLInputEventManager {
public:
	/// Call from the main thread!
	void update();

	Platform::Input::InputSnapshot inEvent;
	OnClickHandler onClickHandler;

private:
	void handleMouseClick();
};

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
