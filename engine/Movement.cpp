#include "Movement.h"

#include <chrono>

using namespace Angina::EngineV3;

void Movement::start(int destX, int destY, int movSpeed) {
	startPos = pos;
	speed = movSpeed;
	dir = Core::Units::calcDirVec(pos, {float(destX), float(destY)});
	const double distance = Core::Units::calcLength(dir);
	timeToDestMs = distance / speed * 1000.0;
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

	const double timeStep = timeSinceStartMs / timeToDestMs;
	const Core::Units::Vec2 dirStep = Core::Units::scale(dir, timeStep);
	pos = Core::Units::addVec(startPos, dirStep);
}