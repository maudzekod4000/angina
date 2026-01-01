#include "BaseInputEventSnapshot.h"

using namespace Angina::Input;
using namespace Angina::Errors;

std::expected<void, ErrorCode> BaseInputEventSnapshot::start()
{
	running = true;
	worker = std::jthread([this]() {
		while (running) {
			auto res = onWorkTick();

			// Give a chance to the client to stop the work.
			if (res.error()) {
				break;
			}
		}

		// TODO: Think about a way to slow down the work so we have finer control on the polling rate.
	});

	return std::expected<void, ErrorCode>();
}

std::expected<void, ErrorCode> BaseInputEventSnapshot::stop()
{
	return std::expected<void, ErrorCode>();
}

InputSnapshot BaseInputEventSnapshot::getSnapshot()
{
	snapshotRequested.store(true, std::memory_order_release);
	return *published.load(std::memory_order_acquire);
}

void BaseInputEventSnapshot::setSnapshot(const InputSnapshot&)
{
	
}
