#include "renderer/primitives/Line.h"

#include "renderer/Renderer.h"

Line::Line(Point aa, Point bb, Color c): a(aa), b(bb), color(c) {}

void Line::draw(Renderer& renderer) {
	renderer.render(*this);
}
