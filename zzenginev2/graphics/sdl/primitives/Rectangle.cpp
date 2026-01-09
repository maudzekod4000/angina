#include "Rectangle.h"

#include "enginev2/graphics/models/Dimensions.h"
#include "enginev2/graphics/models/Point.h"

Rectangle::Rectangle(const Point& pos, const Dimensions& dim, const Color& col, bool filled)
	: rect(SDL_Rect {pos.x, pos.y, dim.w, dim.h}), color(col), fill(filled) {}

Rectangle::Rectangle(const Point& pos, const Dimensions& dim): Rectangle(pos, dim, Color::NONE, false) {}

Rectangle::Rectangle(): Rectangle(Point::UNDEFINED, Dimensions::UNDEFINED) {}

bool Rectangle::operator==(const Rectangle& other) const {
    return rect.x == other.rect.x && rect.y == other.rect.y && rect.w == other.rect.w && rect.h == other.rect.h;
}
