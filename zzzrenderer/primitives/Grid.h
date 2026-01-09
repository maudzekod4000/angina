#ifndef RENDERER_PRIMITIVES_GRID_H_
#define RENDERER_PRIMITIVES_GRID_H_

#include <vector>

#include "renderer/drawable/Drawable.h"
#include "renderer/primitives/Line.h"
#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"

struct Renderer;

class Grid : public Drawable {
public:
	Grid(Point origin, Dimensions dim, float fullWidth, float fullHeight);

	void draw(Renderer&);
private:
	std::vector<Line> lines;
};

#endif /* RENDERER_PRIMITIVES_GRID_H_ */
