#ifndef CORE_UNITS_H
#define CORE_UNITS_H

#include <cstdint>
#include <cassert>
#include <chrono>

namespace Core::Units {

using PositionType = uint16_t;
using Dimension = uint16_t;

using Width = Dimension;
using Height = Dimension;

using AbsPosition = PositionType;

/// Helps catching configuration bugs at compile time and enforces invariants on the rate per second value.
/// Improves the API to the client with a more readable, distinct type.
struct RatePerSecond {
	using RateType = uint16_t;

	explicit constexpr RatePerSecond(RateType v): value(v) {
		constexpr const char msg[] = "Value must be between 1 and 'max'";
		if consteval {
			if (v <= 0 || v > max) {
				throw msg;
			}
		}
		assert(v > 0 && v <= max);
	}

	/// Returns the duration between events, based on the rate per second.
	std::chrono::nanoseconds toNano() const {
		using namespace std::chrono;
		return duration_cast<nanoseconds>(1s) / this->value;
	}

	// Note: Hardcoded value...maybe there is a better way to configure this. Macros or constexprs
	static const RateType max = 120;

	const RateType value;
};

using AbsX = AbsPosition;
using AbsY = AbsPosition;
using FPS = RatePerSecond;

struct Rect {
	int x = 0, y = 0, w = 0, h = 0;
};

struct Vec2 {
	float x = 0.0f, y = 0.0f;
};

// TODO: Inlining these for now but i will extract this class into a separate 
// h and cpp file and there will be no multiple defined symbols problem.
inline Vec2 calcDirVec(const Vec2& src, const Vec2& dst) {
	return { dst.x - src.x, dst.y - src.y };
}

inline double calcLength(const Vec2& v) {
	return sqrt(double(v.x) * v.x + double(v.y) * v.y);
}

inline Vec2 scale(const Vec2& v, double s) {
	return { float(v.x * s), float(v.y * s) };
}

inline Vec2 addVec(const Vec2& a, const Vec2& b) {
	return { a.x + b.x, a.y + b.y };
}

}
#endif