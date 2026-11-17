#include "Movement.h"

#include <chrono>
#include <numeric>
#include <cstdlib>

using namespace Angina::EngineV3;
using namespace Core::Units;

void Movement::start(const Core::Units::Vec2& direction, int movSpeed) {
	dir = direction;
	int prevSpeed = speed;
	speed = movSpeed;
	if (prevSpeed == 0 && onMovementStart) {
		onMovementStart();
	}
}

void Movement::stop() {
	speed = 0;
}

void Movement::update() {
	// well...this is not great at all :D :D :D but i think for first game it will do...
	const Vec2 newPos = addVec(pos, scale(dir, speed));
	if (newPos.x < 0.0f || newPos.y < 0.0f || newPos.x > WINDOW_WIDTH - HERO_WIDTH || newPos.y > WINDOW_HEIGHT) {
		return;
	}
	prevPos = pos;
	pos = newPos;

	if (prevPos.eq(pos) && onMovementEnd) {
		stop();
		onMovementEnd();
	}
}
