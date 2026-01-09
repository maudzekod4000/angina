#include "Point.h"

const Point Point::ZERO(0, 0);
const Point Point::UNDEFINED(10000, 10000);

Point::Point() :
		x(0), y(0) {
}

Point::Point(float inputX, float inputY) :
		x(inputX), y(inputY) {
}

bool Point::operator==(const Point &other) const {
	return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const {
	return !(*this == other);
}

Point Point::operator+(const Point &other) const {
	return {x + other.x, y + other.y};
}

Point Point::operator-(const Point &other) const {
	return {x - other.x, y - other.y};
}

bool Point::operator>(const Point& other) const {
	return x > other.x && y > other.y;
}

std::ostream& operator<<(std::ostream &os, const Point &point) {
	return os << "X: " << point.x << "; Y: " << point.y;
}

