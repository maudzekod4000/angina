#include "LinearFixedMovementManager.h"

#include <iostream>

#include "renderer/primitives/Object.h"
#include "core/math/geometry/Geometry.h"

LinearFixedMovementManager::LinearFixedMovementManager() {}

void LinearFixedMovementManager::addMoveable(Object& moveable) {
	moveables.push_back(&moveable);
}

void LinearFixedMovementManager::processFrame(int64_t elapsedTime) {
	for (Object* moveable : moveables) {
		processMoveable(*moveable, elapsedTime);
	}
}

void LinearFixedMovementManager::processMoveable(Object& moveable, int64_t elapsedTimeMicro) {
	Point currentPos = moveable.getPosition();
	Point destination = moveable.getDestination();

	if (currentPos > destination) {
		return;
	}

	float unitsTravelled = (moveable.getVelocity() * static_cast<float>(elapsedTimeMicro)) / 1000000.0f;
	PointPair lerpedPoint = Geometry::lerp(
			std::make_pair(currentPos.x, currentPos.y),
			std::make_pair(destination.x, destination.y),
			unitsTravelled
	);

	moveable.move(lerpedPoint.first, lerpedPoint.second);
}
