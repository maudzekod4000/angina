#ifndef SDL_PRIMITIVES_DIMENSIONS_H_
#define SDL_PRIMITIVES_DIMENSIONS_H_

struct Dimensions {
	Dimensions();
	Dimensions(float width, float height);

	float w;
	float h;

	static const Dimensions UNDEFINED;
};

#endif /* SDL_PRIMITIVES_DIMENSIONS_H_ */
