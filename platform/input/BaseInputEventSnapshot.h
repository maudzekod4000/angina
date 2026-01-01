#ifndef PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H
#define PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H

#include <thread>
#include <atomic>

#include "IInputEventSnapshot.h"

namespace Angina::Input {

/// Accumulates input events into state object. Does so in a separate thread, which this class manages.
/// Classes, inheriting from this class, will be referred to as 'clients' in the comments.
/// -----------------------
/// Outline of the core idea with double-buffering and requesting snapshots:
/// While no one is requesting snapshots, the client's overriden onWorkTick method will be called
/// on a regular interval. The client has a chance to get the input data from a source system
/// and call setSnapshot, which in turn will write to the current writing snapshot buffer.
/// When getSnapshot is called, a flag 'requested' will be set to true. This will be acknowledged 
/// by the worker thread and, before calling onWorkTick, the write buffer will be swapped and 
/// the published pointer will be changed.
class BaseInputEventSnapshot : public IInputEventSnapshot {
public:
	std::expected<void, Errors::ErrorCode> start() override;
	std::expected<void, Errors::ErrorCode> stop() override;
	InputSnapshot getSnapshot() override;
protected:
	/// Runs on every work tick, on a separate thread.
	/// The client might read input events and call setSnapshot to store them.
	virtual std::expected<void, Errors::ErrorCode> onWorkTick() {}

	/// Writes a snapshot to the current buffer.
	void setSnapshot(const InputSnapshot&);
private:
	std::jthread worker;
	std::atomic_bool running = false; ///< Is the worker thread running?

	InputSnapshot snapshots[2]; ///< Double-buffering of the input events.
	std::atomic<InputSnapshot*> published = nullptr; ///< Pointer to the snapshot which is completely written and safe to read from another thread.
	int writeIdx = 0; ///< Index in the snapshots array marking the snapshot which is safe to write to.
	std::atomic_bool snapshotRequested = false; ///< Client will set this flag via a call to getSnapshot. This will signal the worker thread procedure to swap the buffers.
};
}

#endif // !PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H