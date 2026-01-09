#ifndef RENDERER_PRIMITIVES_TEXT_H_
#define RENDERER_PRIMITIVES_TEXT_H_

#include "renderer/primitives/Object.h"

class Text: public Object {
public:
	Text(Texture&, Dimensions, Point);
};

#endif /* RENDERER_PRIMITIVES_TEXT_H_ */
