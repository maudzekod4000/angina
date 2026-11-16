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
	Movement(int posX, int posY) : pos(Core::Units::Vec2{ float(posX), float(posY) }) {}

	void start(const Core::Units::Vec2& dir, int movSpeed);

	void stop();

	void update();

	Core::Units::Vec2 pos; // These are the GameObject positions.
	OnMovementStart onMovementStart; // TODO: Remove these from here and deal with this another way.
	OnMovementEnd onMovementEnd;
	Core::Units::Vec2 dir; // Normalized.
	int speed = 0;
private:
	Core::Units::Vec2 prevPos;
};
}

#endif // !ENGINE_MOVEMENT_H
