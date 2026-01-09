#ifndef SDL_PRIMITIVES_COLOR_H_
#define SDL_PRIMITIVES_COLOR_H_

#include <cstdint>

struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

	Color();
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	Color(uint8_t r, uint8_t g, uint8_t b);

	static const Color NONE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color BLACK;
};

#endif /* SDL_PRIMITIVES_COLOR_H_ */
