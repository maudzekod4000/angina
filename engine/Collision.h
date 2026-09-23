#ifndef ENGINE_COLLISION_H
#define ENGINE_COLLISION_H

#include "core/units/Units.hpp"

namespace Angina::EngineV3 {
	// So basically we will have a vector of these
	// and we will mark the respective object as 'hasCollision'
	// then, later when we resoslve the collisions we can go through
	// the Collision vector and calculate the resolution based on the collision dir
	// we can also update the respecitve Movement.
	// By making that Collision vector roughly the same size during the life of the program
	// we reduce the number of allocations and dealocations happening.
	struct Collision {
		bool hasCollision = false;
		Core::Units::Vec2 dir; // Normalized.
	};
}

#endif // !ENGINE_COLLISION_H
