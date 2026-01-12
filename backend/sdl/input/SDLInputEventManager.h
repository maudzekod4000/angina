#ifndef PLATFORM_INPUT_EVENT_MANAGER_H
#define PLATFORM_INPUT_EVENT_MANAGER_H

#include <memory>

#include "platform/input/BaseInputEventManager.h"
#include "core/error/Errors.h"

union SDL_Event;

namespace Backend::SDL::Input {

class SDLInputEventManager : public Platform::Input::BaseInputEventManager {
public:
	static std::unique_ptr<SDLInputEventManager> make();

	/// Call from the main thread!
	Core::Errors::ErrorCode update(Platform::System::Phase) override;
private:
	explicit SDLInputEventManager();
};

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
