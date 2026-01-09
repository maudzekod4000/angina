#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <utility>
#include <vector>

#include "enginev2/models/GameObject.h"
#include "enginev2/graphics/models/Point.h"
#include "enginev2/components/ID.h"

struct CollisionData {
	const GameObject& o1;
	const GameObject& o2;
	Point N;
};

struct CollisionDetector {
	std::vector<CollisionData> detectCollisions(const std::vector<GameObject>& gameObjects);
};

#endif // !COLLISION_DETECTOR_H
