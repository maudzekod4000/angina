#ifndef ENGINE_MOVEMENT_H
#define ENGINE_MOVEMENT_H

#include "core/units/Units.hpp"
#include "core/time/Stopwatch.h"

namespace Angina::EngineV3 {
struct Movement {

	Movement() = default;
	Movement(int posX, int posY) : pos(Core::Units::Vec2{ float(posX), float(posY) }) {}

	void start(int destX, int destY, int movSpeed);

	void stop();

	void update();

	Core::Units::Vec2 pos; // These are the GameObject positions.
private:
	Core::Units::Vec2 startPos;
	Core::Units::Vec2 dir; // Calculated on start.
	double timeToDestMs = 0; // Precalculated based on the distance to destination.
	int speed = 0; // Pixels per 1 s
	Core::Time::Stopwatch clock;
};
}

#endif // !ENGINE_MOVEMENT_H
