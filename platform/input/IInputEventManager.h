#ifndef PLATFORM_IINPUT_EVENT_MANAGER_H
#define PLATFORM_IINPUT_EVENT_MANAGER_H

#include <memory>

#include "core/error/Errors.h"
#include "platform/system/Updateable.h"

namespace Platform::Input {

/// Accumulated state (snapshot) of the user input events.
/// As the engine does not need every individual event, the incoming events are reduced to their latest values.
struct InputSnapshot {
	bool quit = false;
};

/// Interface for a family of classes that accumulate and provide read access to
/// accumulated input state.
/// TODO: Jesus....it didn't occur to me that the events should be received on the main thread.
/// So this class can be assumed to be used from the same thread. Although, getSnapshot should be synchronized.
/// I think we need a method to update the snapshot by polling and the double-buffering can stay.
class IInputEventManager : public Platform::System::Updateable {
public:
	virtual ~IInputEventManager() = default;
	virtual InputSnapshot getSnapshot() = 0;
};

using InputEventManagerPtr = std::unique_ptr<Input::IInputEventManager>;

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
