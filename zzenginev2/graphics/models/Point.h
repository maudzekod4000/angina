#ifndef SDL_PRIMITIVES_POINT_H_
#define SDL_PRIMITIVES_POINT_H_

#include <iostream>
#include <cstdint>

struct Point {
	Point();
	Point(int32_t x, int32_t y);

	int32_t x;
	int32_t y;

	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;
	bool operator>(const Point&) const;
	Point operator+(const Point&) const;
	Point operator-(const Point&) const;
	Point operator*(float scalar) const;
	float dot(const Point&) const;
	Point reflect(const Point&) const;

	static const Point ZERO;
	static const Point UNDEFINED;

	friend std::ostream& operator<<(std::ostream&, const Point&);
};

Point operator*(int32_t scalar, const Point& p);

Point operator*(const Point& p, int32_t scalar);

Point operator/(const Point& p, int32_t scalar);

#endif /* SDL_PRIMITIVES_POINT_H_ */
