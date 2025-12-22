#ifndef PLATFORM_INPUT_EVENT_SNAPSHOT_H
#define PLATFORM_INPUT_EVENT_SNAPSHOT_H

import errors;

#include <expected>

namespace Angina::Input {

struct InputSnapshot {
	bool quit = false;
};

class IInputEventSnapshot {
public:
	virtual std::expected<void, Errors::ErrorCode> start() = 0;
	virtual std::expected<void, Errors::ErrorCode> stop() = 0;
	virtual InputSnapshot getSnapshot() = 0;
};
}

#endif // !PLATFORM_INPUT_EVENT_SNAPSHOT_H
