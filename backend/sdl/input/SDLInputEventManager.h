#ifndef PLATFORM_INPUT_EVENT_MANAGER_H
#define PLATFORM_INPUT_EVENT_MANAGER_H

#include "platform/input/BaseInputEventManager.h"

namespace Backend::SDL::Input {

class SDLInputEventManager {
public:
	/// Call from the main thread!
	void update(Platform::System::Phase);

	Platform::Input::InputSnapshot inEvent;
};

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
