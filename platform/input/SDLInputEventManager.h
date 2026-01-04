#ifndef PLATFORM_INPUT_EVENT_MANAGER_H
#define PLATFORM_INPUT_EVENT_MANAGER_H

import errors;
import units;

#include <expected>
#include <memory>

#include "BaseInputEventManager.h"

union SDL_Event;

namespace Angina::Input {

class SDLInputEventManager : public BaseInputEventManager {
public:
	static std::unique_ptr<SDLInputEventManager> make(InputRefreshRate);
	std::expected<void, Errors::ErrorCode> onWorkTick() override;
private:
	explicit SDLInputEventManager(InputRefreshRate);
	/// Maps an SDL_Event to own event object.
	InputSnapshot mapEvent(SDL_Event);
};

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
