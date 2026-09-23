#include "Movement.h"

#include <chrono>

using namespace Angina::EngineV3;

void Movement::start(int destX, int destY, int movSpeed) {
	startPos = pos;
	speed = movSpeed;
	path = Core::Units::calcDirVec(pos, {float(destX), float(destY)});
	dir = Core::Units::normalize(path);
	const double distance = Core::Units::calcLength(path);
	timeToDestMs = distance / speed * 1000.0;
	if (onMovementStart) onMovementStart();
	clock.reset();
}

void Movement::stop() {
	speed = 0;
	if (onMovementEnd) onMovementEnd();
}

void Movement::update() {
	if (speed == 0) return;

	const long long timeSinceStartMs = std::chrono::duration_cast<std::chrono::milliseconds>(clock.elapsed()).count();
			
	if (timeSinceStartMs >= timeToDestMs) {
		stop();
		return;
	}

	const double timeStep = timeSinceStartMs / timeToDestMs;
	const Core::Units::Vec2 dirStep = Core::Units::scale(path, timeStep);
	pos = Core::Units::addVec(startPos, dirStep);
}