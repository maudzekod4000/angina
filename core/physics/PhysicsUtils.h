#ifndef CORE_PHYSICS_UTILS_H
#define CORE_PHYSICS_UTILS_H

namespace Core::PhysicsUtils {
	// assumes top-left corner of rect as coordinates
	inline bool rectIntersect(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh) {
		return ax <= bx + bw && ax + aw >= bx &&
			ay >= by - bh && ay - ah <= by;
	}
}

#endif // !CORE_PHYSICS_UTILS_H
