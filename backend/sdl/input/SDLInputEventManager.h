#ifndef PLATFORM_INPUT_EVENT_MANAGER_H
#define PLATFORM_INPUT_EVENT_MANAGER_H

#include <memory>

#include "platform/input/BaseInputEventManager.h"
#include "core/error/Errors.h"

namespace Backend::SDL::Input {

class SDLInputEventManager : public Platform::Input::BaseInputEventManager {
public:
	SDLInputEventManager() = default;

	/// Call from the main thread!
	Core::Errors::ErrorCode update(Platform::System::Phase) override;
};

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
