#ifndef SDL_PRIMITIVES_DIMENSIONS_H_
#define SDL_PRIMITIVES_DIMENSIONS_H_

#include <cstdint>

struct Dimensions {
	Dimensions();
	Dimensions(uint16_t width, uint16_t height);

	uint16_t w;
	uint16_t h;

	static const Dimensions UNDEFINED;
};

#endif /* SDL_PRIMITIVES_DIMENSIONS_H_ */
