#ifndef CORE_UNITS_H
#define CORE_UNITS_H

#include <cstdint>
#include <cassert>
#include <chrono>

namespace Angina::Units {

// Notes: I am a bit unsure of the implementation of these classes and the use of asserts.
// I think, as long as the class is instantiated dynamically by the gameplay logic, it is fine to 
// have asserts.
// The intention of these classes is to configure various subsystems and objects,
// but if I start using them to dynamically create objects with non-deterministic data,
// then i suppose there should be some validation before creating the objects, in some factory method.
// The benefit of having some assertions is that while I am developing a game I can be guarded and 
// warned about wrong uses of the object.
struct Dimension {
	explicit constexpr Dimension(uint32_t v): value(v) {
		constexpr const char msg[] = "Value must be > 0";
		if consteval {
			if (v <= 0) {
				throw msg;
			}
		}
		else {
			assert(v > 0 && msg);
		}
	}

	const uint32_t value;
};

using Width = Dimension;
using Height = Dimension;

struct AbsPosition {
	explicit constexpr AbsPosition(uint32_t p) : value(p) {}

	const uint32_t value;
};

/// Helps catching configuration bugs at compile time and enforces invariants on the rate per second value.
/// Improves the API to the client with a more readable, distinct type.
struct RatePerSecond {
	explicit constexpr RatePerSecond(uint32_t v): value(v) {
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
	static const uint32_t max = 120;

	const uint32_t value;
};

using AbsX = AbsPosition;
using AbsY = AbsPosition;

}
#endif