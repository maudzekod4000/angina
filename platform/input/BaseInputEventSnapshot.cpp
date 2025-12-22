#include "BaseInputEventSnapshot.h"

using namespace Angina::Input;
using namespace Angina::Errors;

std::expected<void, ErrorCode> BaseInputEventSnapshot::start()
{
	worker = std::jthread([this]() {

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
