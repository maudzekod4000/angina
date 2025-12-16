#ifndef INIT_SUBSYSTEM_LIFECYCLE_MANAGERS_H
#define INIT_SUBSYSTEM_LIFECYCLE_MANAGERS_H

#include <vector>
#include <memory>

#include "ISubsystemLifecycleManager.h"

namespace Angina::Init {
class SubsystemLifecycleManagers final : public ISubsystemLifecycleManager {
public:
	explicit SubsystemLifecycleManagers(const std::vector<std::shared_ptr<ISubsystemLifecycleManager>>&);

	// TODO: The flags thing is not very clear...no flags so far so lets skip this detail for now.
	std::expected<void, Errors::ErrorCode> init(uint64_t flags) override;
	std::expected<void, Errors::ErrorCode> destroy() override;
	bool isCriticalSubsystem() override;
private:
	std::vector<std::shared_ptr<ISubsystemLifecycleManager>> lifecycleManagers;
};
}

#endif // !INIT_SUBSYSTEM_LIFECYCLE_MANAGERS_H
