#include "Line.h"

Line::Line(const Point& start, const Point& end, const Color& clr): a(start), b(end), color(clr) {}

Line::Line(const Point& start, const Point& end, const Point& normal): a(start), b(end), color(Color::BLACK), N(normal)
{
}

Point Line::getOrigin() const {
  return a;
}

Point Line::getEnd() const {
  return b;
}

Line Line::operator+(const Line& other) const {
	return Line(a, b + other.b, Color::BLACK);
}

Line Line::operator*(int32_t scalar) {
	return Line(a, b * scalar, color);
}

Line Line::operator/(int32_t scalar) {
  return Line(a, b / scalar, color);
}

std::ostream& operator<<(std::ostream& os, const Line& line) {
  return os << line.a << " " << line.b;
}

Line Line::connect(const Line& other) const {
  return Line(this->b, other.b, Color::BLACK);
}

Line Line::midpoint(const Line& other) const {
  return (*this + other) / 2;
}

Line Line::reversed() const {
  return Line(b, a, color);
}
