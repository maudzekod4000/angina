#include "BaseInputEventManager.h"

using namespace Platform::Input;
using namespace Core::Errors;

BaseInputEventManager::BaseInputEventManager() {
}

InputSnapshot BaseInputEventManager::getSnapshot()
{
	std::shared_lock readLock(snapshotMutex);
	return snapshot;
}

// Note: It is not clear how this class is going to be used..
// Maybe there will be no need for thread-safety.
void BaseInputEventManager::setSnapshot(const InputSnapshot& s)
{
	std::unique_lock writeLock(snapshotMutex);
	snapshot = s;
}
