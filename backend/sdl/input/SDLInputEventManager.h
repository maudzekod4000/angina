#ifndef PLATFORM_INPUT_EVENT_MANAGER_H
#define PLATFORM_INPUT_EVENT_MANAGER_H

#include <memory>

#include "platform/input/BaseInputEventManager.h"
#include "core/error/Errors.h"

union SDL_Event;

namespace Angina::Input {

class SDLInputEventManager : public BaseInputEventManager {
public:
	static std::unique_ptr<SDLInputEventManager> make();

	/// Call from the main thread!
	Errors::ErrorCode update() override;
private:
	explicit SDLInputEventManager();

	/// Maps an SDL_Event to own event object.
	InputSnapshot mapEvent(SDL_Event);
};

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
