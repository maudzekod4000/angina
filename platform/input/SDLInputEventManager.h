#ifndef PLATFORM_INPUT_EVENT_MANAGER_H
#define PLATFORM_INPUT_EVENT_MANAGER_H

import errors;

#include <expected>

#include "BaseInputEventManager.h"

union SDL_Event;

namespace Angina::Input {

class SDLInputEventManager : public BaseInputEventManager {
public:
	explicit SDLInputEventManager(InputRefreshRate);

	std::expected<void, Errors::ErrorCode> onWorkTick() override;

private:
	/// Maps an SDL_Event to own event object.
	InputSnapshot mapEvent(SDL_Event);
};

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
