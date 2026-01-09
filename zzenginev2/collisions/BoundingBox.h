#ifndef ENGINEV2_COLLISIONS_BOUNDING_BOX_H
#define ENGINEV2_COLLISIONS_BOUNDING_BOX_H

#include "enginev2/graphics/models/Point.h"
#include "enginev2/graphics/models/Line.h"
#include "enginev2/graphics/sdl/primitives/Rectangle.h"

class BoundingBox {
public:
	BoundingBox() : min(Point()), max(Point()) {}
	BoundingBox(Point min, Point max) : min(min), max(max) {}
	void add(const Rectangle&);
	bool intersects(const BoundingBox& other) const;
	bool intersects(const Line& line) const;

	Point min;
	Point max;
};

#endif // !ENGINEV2_COLLISIONS_BOUNDING_BOX_H
