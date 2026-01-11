#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

#include "core/error/Errors.h"

namespace Platform::System {

/// Represents a subsystem which requires updates, usually on an interval, i.e. Input, Animation, Physics
class Updateable {
public:
	virtual ~Updateable() = default;
	virtual Core::Errors::ErrorCode update() = 0;
};
// TODO: Maybe the *Manager classes should be called System.
}

#endif // !ENGINE_SYSTEM_H
