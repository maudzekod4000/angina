#ifndef ENGINEV2_GRAPHICS_COMMONS_PRIMITIVES_PIXEL_H_
#define ENGINEV2_GRAPHICS_COMMONS_PRIMITIVES_PIXEL_H_

#include "enginev2/graphics/models/Point.h"
#include "enginev2/graphics/models/Color.h"

class TextureRendererComponent;

class Pixel {
public:
	friend class TextureRendererComponent;

	Pixel(const Point&, const Color&);
private:
	Point position;
	Color color;
};

#endif /* ENGINEV2_GRAPHICS_COMMONS_PRIMITIVES_PIXEL_H_ */
