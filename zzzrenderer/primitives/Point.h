#ifndef SDL_PRIMITIVES_POINT_H_
#define SDL_PRIMITIVES_POINT_H_

#include <iostream>

/**
 * I am also using this struct as a 2D vector...Hopefully that does not backfire...
 */
struct Point {
	Point();
	Point(float x, float y);

	float x;
	float y;

	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;
	bool operator>(const Point&) const;
	Point operator+(const Point&) const;
	Point operator-(const Point&) const;

	static const Point ZERO;
	static const Point UNDEFINED;

	friend std::ostream& operator<<(std::ostream&, const Point&);
};

#endif /* SDL_PRIMITIVES_POINT_H_ */
