module;

#include <cstdint>
#include <cassert>

export module units;

namespace Angina::Units {

struct Dimension {
	explicit constexpr Dimension(uint32_t w): value(w) {
		assert(w > 0);
	}

	const uint32_t value;
};

export using Width = Dimension;
export using Height = Dimension;

struct AbsPosition {
	explicit constexpr AbsPosition(uint32_t p) : value(p) {
		assert(p >= 0);
	}

	const uint32_t value;
};

export using AbsX = AbsPosition;
export using AbsY = AbsPosition;

}
