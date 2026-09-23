#ifndef ENGINE_MOVEMENT_H
#define ENGINE_MOVEMENT_H

#include <functional>

#include "core/units/Units.hpp"
#include "core/time/Stopwatch.h"

namespace Angina::EngineV3 {

using OnMovementStart = std::function<void()>;
using OnMovementEnd = std::function<void()>;

struct Movement {

	Movement() = default;
	Movement(int posX, int posY) : pos(Core::Units::Vec2{ float(posX), float(posY) }),
		prevPos(pos) {}

	void start(int destX, int destY, int movSpeed);

	void stop();

	void update();

	Core::Units::Vec2 pos; // These are the GameObject positions.
	OnMovementStart onMovementStart; // TODO: Remove these from here and deal with this another way.
	OnMovementEnd onMovementEnd;
	Core::Units::Vec2 dir; // Normalized.
	Core::Units::Vec2 prevPos;
private:
	Core::Units::Vec2 startPos;
	Core::Units::Vec2 path; // Calculated on start.
	double timeToDestMs = 0; // Precalculated based on the distance to destination.
	int speed = 0; // Pixels per 1 s
	Core::Time::Stopwatch clock;
};
}

#endif // !ENGINE_MOVEMENT_H
