#ifndef RENDERER_PRIMITIVES_LINE_H_
#define RENDERER_PRIMITIVES_LINE_H_

#include "renderer/primitives/Point.h"
#include "renderer/drawable/Drawable.h"
#include "renderer/primitives/Color.h"

struct Renderer;

struct Line : public Drawable {
	Line(Point aa, Point bb, Color c);

	Point a;
	Point b;
	Color color;

	void draw(Renderer&);
};

#endif /* RENDERER_PRIMITIVES_LINE_H_ */
