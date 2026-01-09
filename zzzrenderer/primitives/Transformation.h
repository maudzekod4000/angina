#ifndef RENDERER_PRIMITIVES_TRANSFORMATION_H_
#define RENDERER_PRIMITIVES_TRANSFORMATION_H_

#include "platform/sdl/enums/Flip.h"

struct Transformation {
	Transformation();

	double rotation;
	Flip flip;
};

#endif /* RENDERER_PRIMITIVES_TRANSFORMATION_H_ */
