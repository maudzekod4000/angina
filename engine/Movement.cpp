#include "Movement.h"

#include <chrono>

using namespace Angina::EngineV3;

void Movement::start(int destX, int destY, int movSpeed) {
	startPos = pos;
	speed = movSpeed;
	dir = Core::Units::calcDirVec(pos, {float(destX), float(destY)});
	const float distance = Core::Units::calcLength(dir);
	timeToDestMs = int(distance / speed * 1000.0f);
	clock.reset();
}

void Movement::stop() {
	speed = 0;
}

void Movement::update() {
	if (speed == 0) return;

	const long long timeSinceStartMs = std::chrono::duration_cast<std::chrono::milliseconds>(clock.elapsed()).count();
			
	if (timeSinceStartMs >= timeToDestMs) {
		stop();
		return;
	}

	const float timeStep = timeSinceStartMs / float(timeToDestMs);
	const Core::Units::Vec2 dirStep = Core::Units::scale(dir, timeStep);
	pos = Core::Units::addVec(startPos, dirStep);
}