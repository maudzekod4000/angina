#include "BaseInputEventManager.h"

using namespace Platform::Input;
using namespace Core::Errors;

BaseInputEventManager::BaseInputEventManager() {
	publishedSnapshot = &snapshots[1 - writeIdx];
}

InputSnapshot BaseInputEventManager::getSnapshot()
{
	snapshotRequested.store(true, std::memory_order_release);
	return *publishedSnapshot.load(std::memory_order_acquire);
}

void BaseInputEventManager::setSnapshot(const InputSnapshot& s)
{
	if (snapshotRequested.exchange(false)) {
		const int readIdx = writeIdx.load(std::memory_order_acquire);
		publishedSnapshot.store(&snapshots[readIdx], std::memory_order_release);
		writeIdx.store(1 - readIdx, std::memory_order_release);
	}

	const int currentIdx = writeIdx.load(std::memory_order_acquire);
	snapshots[currentIdx] = s;
}
