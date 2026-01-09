#ifndef ENGINEV2_GRAPHICS_SDL_PRIMITIVES_RECTANGLE_H_
#define ENGINEV2_GRAPHICS_SDL_PRIMITIVES_RECTANGLE_H_

#include "SDL_shape.h"

#include "enginev2/graphics/models/Color.h"

struct Dimensions;
struct Point;
class TextureRendererComponent;

class Rectangle {
public:
	friend class TextureRendererComponent;
	friend class GameObject;

	Rectangle();

	Rectangle(
				const Point& pos,
				const Dimensions& dim);

	Rectangle(
			const Point& pos,
			const Dimensions& dim,
			const Color& color,
			bool fill = false);

	bool operator==(const Rectangle&) const;
private:
	SDL_Rect rect;
	Color color;
	bool fill;
};

#endif /* ENGINEV2_GRAPHICS_SDL_PRIMITIVES_RECTANGLE_H_ */
