#ifndef SDL_PRIMITIVES_RECT_H_
#define SDL_PRIMITIVES_RECT_H_

#include <iostream>

#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"
#include "renderer/primitives/Color.h"
#include "renderer/drawable/Drawable.h"

#include "SDL_shape.h"

class Rect: public Drawable {
public:
	Rect(Point, Dimensions, Color);
	Rect(float x, float y, float w, float h, const Color& = Color::NONE);

	void draw(Renderer&);

	bool operator==(const Rect&) const;
	bool operator!=(const Rect&) const;

	SDL_FRect getRawRect() const;
	SDL_Rect toIntRect() const;
	Color getColor() const;

	bool isInRect(const Point&);

	static const Rect ZERO;
	static const Rect UNDEFINED;

	friend std::ostream& operator<<(std::ostream&, const Rect&);
private:
	SDL_FRect rect;
	Color color;
};

#endif /* SDL_PRIMITIVES_RECT_H_ */
