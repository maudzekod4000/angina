#include "Movement.h"

#include <chrono>
#include <numeric>
#include <cstdlib>

using namespace Angina::EngineV3;
using namespace Core::Units;

void Movement::start(int destX, int destY, int movSpeed) {
	prevPos = startPos = pos;
	path = Core::Units::calcDirVec(pos, {float(destX), float(destY)});
	dir = Core::Units::normalize(path);
	const double distance = Core::Units::calcLength(path);
	timeToDestMs = distance / movSpeed * 1000.0;
	if (onMovementStart && speed == 0) onMovementStart();
	speed = movSpeed;
	clock.reset();
}

void Movement::start(const Core::Units::Vec2& direction, float step, int movSpeed) {
	const Vec2 dest = addVec(pos, scale(direction, step));

	start(int(dest.x), int(dest.y), movSpeed);
}

void Movement::stop() {
	if (onMovementEnd && speed != 0) onMovementEnd();
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
	const Core::Units::Vec2 dirStep = Core::Units::scale(path, timeStep);
	prevPos = pos;
	pos = Core::Units::addVec(startPos, dirStep);
}