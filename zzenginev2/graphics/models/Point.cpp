#include "Point.h"

const Point Point::ZERO(0, 0);
const Point Point::UNDEFINED(10000, 10000);

Point::Point() :
		x(0), y(0) {
}

Point::Point(int32_t inputX, int32_t inputY) :
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

Point Point::operator*(float s) const
{
	return Point(x * s, y * s);
}

float Point::dot(const Point& other) const
{
	return this->x * other.x + this->y * other.y;
}

Point Point::reflect(const Point& other) const
{
	return *this - (other * this->dot(other) * 2);
}

bool Point::operator>(const Point& other) const {
	return x > other.x && y > other.y;
}

Point operator*(int32_t scalar, const Point& p) {
	return {p.x * scalar, p.y * scalar};
}

Point operator*(const Point& p, int32_t scalar) {
	return {p.x * scalar, p.y * scalar};
}

Point operator/(const Point& p, int32_t scalar) {
  return {p.x / scalar, p.y / scalar};
}

std::ostream& operator<<(std::ostream &os, const Point &point) {
	return os << "X: " << point.x << "; Y: " << point.y;
}

