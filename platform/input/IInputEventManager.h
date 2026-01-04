#ifndef PLATFORM_IINPUT_EVENT_MANAGER_H
#define PLATFORM_IINPUT_EVENT_MANAGER_H

import errors;

#include <memory>
#include <expected>

namespace Angina::Input {

/// Accumulated state (snapshot) of the user input events.
/// As the engine does not need every individual event, the incoming events are reduced to their latest values.
struct InputSnapshot {
	bool quit = false;
};

/// Interface for a family of classes that accumulate and provide read access to
/// accumulated input state.
class IInputEventManager {
public:
	virtual std::expected<void, Errors::ErrorCode> start() = 0;
	virtual std::expected<void, Errors::ErrorCode> stop() = 0;
	virtual InputSnapshot getSnapshot() = 0;
};

using InputEventManagerPtr = std::unique_ptr<Input::IInputEventManager>;

}

#endif // !PLATFORM_INPUT_EVENT_MANAGER_H
