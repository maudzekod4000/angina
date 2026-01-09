#include "Grid.h"

#include <cstdint>

#include "renderer/Renderer.h"

Grid::Grid(Point origin, Dimensions dim, float fullWidth, float fullHeight) {
	int32_t horizontalLinesCount = static_cast<int32_t>((fullHeight / dim.h) - 1);

	for (int32_t i = 0; i < horizontalLinesCount; i++) {
		float startPointY = origin.y + (dim.h * (static_cast<float>(i) + 1.0f));
		float startPointX = origin.x;
		float endPointY = startPointY;
		float endPointX = fullWidth;

		Line line = {
				Point{startPointX, startPointY},
				Point{endPointX, endPointY},
				Color::RED
		};

		lines.push_back(line);
	}

	int32_t verticalLinesCount = static_cast<int32_t>(fullWidth / dim.w);

	for (int32_t i = 0; i < verticalLinesCount; i++) {
		float startPointY = origin.y;
		float startPointX = origin.x + (dim.w * (static_cast<float>(i) + 1.0f));
		float endPointY = fullHeight;
		float endPointX = startPointX;

		Line line = {
				Point{startPointX, startPointY},
				Point{endPointX, endPointY},
				Color::RED
		};

		lines.push_back(line);
	}
}

void Grid::draw(Renderer& renderer) {
	for (Line& line : lines) {
		renderer.render(line);
	}
}
