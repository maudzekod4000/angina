#ifndef ENGINE_BASIC_MOVEMENT_H
#define ENGINE_BASIC_MOVEMENT_H

#include <functional>

#include "core/units/Units.hpp"

namespace Angina::EngineV3 {

using OnMovementStart = std::function<void()>;
using OnMovementEnd = std::function<void()>;

struct BasicMovement {
	BasicMovement() = default;
	BasicMovement(int x, int y) : pos(float(x), float(y)), dest(pos) {}

	// I am not sure what this will do? I suppose it is better if move sets up the destination
	// and the update actually moves it.
	void update();

	// THis is a simple 'step' movement, meaning that this is an instant movement by this amount.
	// This is not very nice but it will do for starts.
	void move(const Core::Units::Vec2& dir, float step);

	void stop();

	// Ok so...we can track whether we have continuous change in position
	// if there is a period without change we can emit a stop()
	// or something like a debounce on the start method

	Core::Units::Vec2 pos;
	OnMovementStart onStart;
	OnMovementEnd onEnd;
	Core::Units::Vec2 direction;
private:
	Core::Units::Vec2 dest;
};
}

#endif // !ENGINE_BASIC_MOVEMENT_H
