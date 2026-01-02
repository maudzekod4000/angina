#ifndef PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H
#define PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H

import units;

#include <thread>
#include <atomic>
#include <stop_token>

#include "IInputEventSnapshot.h"

namespace Angina::Input {

// Constrained type wont allow too small or too big refresh rate.
// Having a high refresh rate would provide the freshest input data, but for some applications
// that may be an overkill and will put strain on the input thread.
using InputRefreshRate = Units::BoundedInt<1, 120>;

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
/// Lock-free, thread-safe in the case of single reader and writer.
/// Haven't thought about multiple writers and single reader...Although that scenario I will avoid.
/// start() and stop() should be called from the same thread.
/// getSnapshot and setSnapshot can be called from separate threads safely.
class BaseInputEventSnapshot : public IInputEventSnapshot {
public:
	explicit BaseInputEventSnapshot(InputRefreshRate);

	/// Starts the worker thread.
	std::expected<void, Errors::ErrorCode> start() override;

	/// Gracefully shuts down the worker thread.
	std::expected<void, Errors::ErrorCode> stop() override;

	/// @return Eventually consistent snapshot of the input state.
	InputSnapshot getSnapshot() override;
protected:
	/// Runs on every work tick, on a separate thread.
	/// The client might read input events and call setSnapshot to store them.
	virtual std::expected<void, Errors::ErrorCode> onWorkTick() = 0;

	/// Writes a snapshot to the current buffer.
	void setSnapshot(const InputSnapshot&);
private:
	std::jthread worker;

	InputSnapshot snapshots[2]; ///< Double-buffering of the input events.
	std::atomic<InputSnapshot*> publishedSnapshot = nullptr; ///< Pointer to the snapshot which is completely written and safe to read from another thread.
	std::atomic_int writeIdx = 0; ///< Index in the snapshots array marking the snapshot which is safe to write to.
	std::atomic_bool snapshotRequested = false; ///< Client will set this flag via a call to getSnapshot. This will signal the worker thread procedure to swap the buffers.
	InputRefreshRate refreshRate; ///< How quickly should the system check for new input data?

	/// Procedure (work unit) to run on the worker thread.
	/// @param s Allows for graceful termination of the thread, after the work (iteration)
	/// has completed fully.
	void workerProc(std::stop_token s);
};
}

#endif // !PLATFORM_BASE_INPUT_EVENT_SNAPSHOT_H