#ifndef INIT_SUBSYSTEM_INITIALIZER_H
#define INIT_SUBSYSTEM_INITIALIZER_H

import errors;

#include <expected>
#include <cstdint>

namespace Angina::Init {
/// Sometimes, subsystems need initialization/deinitialization. For example, SDL's graphics and audio systems need to be started, before doing anything useful with them.
/// And at the end they need to be cleaned up.
/// Note: Make sure the implementations are trivially copiable/assignable, preferably, without any state.
class ISubsystemLifecycleManager {
public:
	virtual std::expected<void, Errors::ErrorCode> init(uint64_t flags) = 0;
	virtual std::expected<void, Errors::ErrorCode> destroy() = 0;
};
}

#endif // !INIT_SUBSYSTEM_INITIALIZER_H
