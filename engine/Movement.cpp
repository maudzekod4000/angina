#include "Movement.h"

#include <chrono>
#include <numeric>
#include <cstdlib>

using namespace Angina::EngineV3;
using namespace Core::Units;

void Movement::start(int destX, int destY, int movSpeed) {
	if (speed != 0) return;
	prevPos = startPos = pos;
	path = Core::Units::calcDirVec(pos, {float(destX), float(destY)});
	dir = Core::Units::normalize(path);
	const double distance = Core::Units::calcLength(path);
	timeToDestMs = distance / movSpeed * 1000.0;
	if (onMovementStart) onMovementStart();
	speed = movSpeed;
	clock.reset();
	std::puts("restarted mov");
}

void Movement::start(const Core::Units::Vec2& direction, float step, int movSpeed) {

	// Sooo there are three options here:
	// 1. The movement is moving in the same direction
	//    - That means we should move the destination further away and recalculate the time
	// 2. The movement is in another direction
	//    - stop the current movement and start another one in the other direction.
	// 3. The movement is not moving at all, so we can just start it normally.
	if (!isMoving()) {
		const Vec2 dest = addVec(pos, scale(direction, step));

		start(int(dest.x), int(dest.y), movSpeed);
		return;
	}


}

void Movement::stop() {
	if (speed == 0) return;
	if (onMovementEnd) onMovementEnd();
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