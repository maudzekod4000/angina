#include "Units.hpp"

using namespace Core::Units;

bool Vec2::eq(const Vec2& other) const {
	return fabs(x - other.x) < std::numeric_limits<float>::epsilon() &&
		fabs(y - other.y) < std::numeric_limits<float>::epsilon();
}

float Vec2::len() const {
	return sqrtf(x * x + y * y);
}
