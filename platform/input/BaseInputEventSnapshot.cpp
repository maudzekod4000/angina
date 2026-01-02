#include "BaseInputEventSnapshot.h"

using namespace Angina::Input;
using namespace Angina::Errors;

BaseInputEventSnapshot::BaseInputEventSnapshot(InputRefreshRate r): refreshRate(r) {}

std::expected<void, ErrorCode> BaseInputEventSnapshot::start()
{
	worker = std::jthread([this](std::stop_token t) { workerProc(t); });

	return std::expected<void, ErrorCode>();
}

std::expected<void, ErrorCode> BaseInputEventSnapshot::stop()
{
	worker.request_stop();
	return std::expected<void, ErrorCode>();
}

InputSnapshot BaseInputEventSnapshot::getSnapshot()
{
	snapshotRequested.store(true, std::memory_order_release);
	return *publishedSnapshot.load(std::memory_order_acquire);
}

void BaseInputEventSnapshot::setSnapshot(const InputSnapshot& s)
{
	if (snapshotRequested.exchange(false)) {
		const int readIdx = writeIdx.load(std::memory_order_acquire);
		publishedSnapshot.store(&snapshots[readIdx], std::memory_order_release);
		writeIdx.store(1 - readIdx, std::memory_order_release);
	}

	const int currentIdx = writeIdx.load(std::memory_order_acquire);
	snapshots[currentIdx] = s;
}

void BaseInputEventSnapshot::workerProc(std::stop_token stopToken)
{
	while (!stopToken.stop_requested()) {
		auto res = onWorkTick();

		// Give a chance to the client to stop the work.
		if (res.error()) {
			break;
		}
	}

	// TODO: Think about a way to slow down the work so we have finer control on the polling rate.
}
