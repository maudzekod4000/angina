#ifndef INIT_SUBSYSTEM_LIFECYCLE_MANAGERS_H
#define INIT_SUBSYSTEM_LIFECYCLE_MANAGERS_H

#include <vector>

#include "ISubsystemLifecycleManager.h"

namespace Angina::Init {
class SubsystemLifecycleManagers {
public:
	explicit SubsystemLifecycleManagers(const std::vector<ISubsystemLifecycleManager>&);
private:

};
}

#endif // !INIT_SUBSYSTEM_LIFECYCLE_MANAGERS_H
