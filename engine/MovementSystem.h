#ifndef ENGINE_MOVEMENT_SYSTEM_H
#define ENGINE_MOVEMENT_SYSTEM_H

#include <vector>

#include "Movement.h"
#include "core/units/Units.hpp"
#include "core/identity/Id.h"

namespace Angina::EngineV3 {

struct MovementCommand {
	Core::Identity::Id movementId;
	Core::Units::Vec2 dest;
	float speed;
};

// Think: The movement and the collision system are not so easy to multithread...
// Maybe i will start with parallelizing the animation system first.
class MovementSystem {
public:

	// This method will go through the enqueued movements and will 
	// update the respectable movement objects
	// This method will work in another thread so it has to be thread-safe.
	void update(std::vector<Movement>&);

	void enqueueMove(const std::vector<Movement>&, MovementCommand);

private:
	std::vector<MovementCommand> commands;
};
}

#endif // !ENGINE_MOVEMENT_SYSTEM_H
