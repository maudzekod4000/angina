#include "SubsystemLifecycleManagers.h"

#include <ranges>

using namespace Angina::Init;
using namespace Angina::Errors;

SubsystemLifecycleManagers::SubsystemLifecycleManagers(const std::vector<std::shared_ptr<ISubsystemLifecycleManager>>& slms): lifecycleManagers(slms) {}

std::expected<void, ErrorCode> SubsystemLifecycleManagers::init(uint64_t flags)
{
	for (auto& lifecycleManager : lifecycleManagers) {
		const auto res = lifecycleManager->init(flags);

		if (isCriticalSubsystem() && !res.has_value()) {
			return res;
		}
	}
	return {};
}

std::expected<void, ErrorCode> Angina::Init::SubsystemLifecycleManagers::destroy()
{
	for (auto& lifecycleManager : std::views::reverse(lifecycleManagers)) {
		const auto res = lifecycleManager->destroy();

		if (isCriticalSubsystem() && !res.has_value()) {
			return res;
		}
	}
	return {};
}

bool Angina::Init::SubsystemLifecycleManagers::isCriticalSubsystem()
{
	return true;
}
