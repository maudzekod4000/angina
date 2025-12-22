#ifndef PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H
#define PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H

#include <thread>
#include <atomic>

#include "IInputEventSnapshot.h"

namespace Angina::Input {
class BaseInputEventSnapshot : public IInputEventSnapshot {
public:
	std::expected<void, Errors::ErrorCode> start() override;
	std::expected<void, Errors::ErrorCode> stop() override;
	InputSnapshot getSnapshot() override;
protected:
	void setSnapshot(const InputSnapshot&);
	InputSnapshot inputEventSnapshot; ///< Accumulated input state from events.
private:
	std::jthread worker;
	std::atomic_bool running = false; ///< Is the worker thread running?

	InputSnapshot snapshots[2];
	std::atomic<InputSnapshot*> published = nullptr;
	int writeIdx = 0;
	std::atomic_bool snapshotRequested = false;
};
}

#endif // !PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H