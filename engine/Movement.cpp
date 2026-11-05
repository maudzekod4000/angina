#include "Movement.h"

#include <chrono>
#include <numeric>
#include <cstdlib>

using namespace Angina::EngineV3;

void Movement::start(int destX, int destY, int movSpeed) {
	prevPos = startPos = pos;
	speed = movSpeed;
	path = Core::Units::calcDirVec(pos, {float(destX), float(destY)});
	dir = Core::Units::normalize(path);
	const double distance = Core::Units::calcLength(path);
	timeToDestMs = distance / speed * 1000.0;
	if (onMovementStart) onMovementStart();
	clock.reset();
}

void Movement::start(const Core::Units::Vec2& movDir, int distance, int movSpeed)
{
	// Hmmmm how to make a smooth movement?
	// Значи хем не е добре да се спира текущото движение понеже става лагаво,
	// но в същото време трябва някак си да знае кода че има 
	if (calcLength(dir) > 0.0f && Core::Units::dot(dir, movDir) == 1.0f && speed != 0) {
		return;
	}

	// So basically, if we are already moving we should not emit onMovementStart again.
	// we just need to recalculate the destination direction and time to dest, without resetting the clock.

	Core::Units::Vec2 dest = addVec(pos, Core::Units::scale(movDir, double(distance)));
	start(int(dest.x), int(dest.y), movSpeed);
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
	prevPos = pos;
	pos = Core::Units::addVec(startPos, dirStep);
}