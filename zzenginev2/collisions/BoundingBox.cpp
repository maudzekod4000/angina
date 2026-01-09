#include "BoundingBox.h"

void BoundingBox::add(const Rectangle&)
{
}

bool BoundingBox::intersects(const BoundingBox& other) const
{
	return this->max.x > other.min.x && other.max.x > this->min.x &&
		this->min.y > other.max.y && other.min.y > this->max.y;
}

bool BoundingBox::intersects(const Line& line) const
{
	BoundingBox bb(line.getOrigin(), line.getEnd());
	return this->intersects(bb);
}
