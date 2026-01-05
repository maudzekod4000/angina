#include "SubsystemLifecycleManagers.h"

#include <ranges>

using namespace Angina::Init;
using namespace Angina::Errors;

SubsystemLifecycleManagers::SubsystemLifecycleManagers(const std::vector<std::shared_ptr<ISubsystemLifecycleManager>>& slms): lifecycleManagers(slms) {}

ErrorCode SubsystemLifecycleManagers::init(uint64_t flags)
{
	for (auto& lifecycleManager : lifecycleManagers) {
		const auto err = lifecycleManager->init(flags);

		if (isCriticalSubsystem() && err) {
			return err;
		}
	}
	return ErrorCode();
}

ErrorCode SubsystemLifecycleManagers::destroy()
{
	for (auto& lifecycleManager : std::views::reverse(lifecycleManagers)) {
		const auto err = lifecycleManager->destroy();

		if (isCriticalSubsystem() && err) {
			return err;
		}
	}
	return {};
}

bool Angina::Init::SubsystemLifecycleManagers::isCriticalSubsystem()
{
	return true;
}
