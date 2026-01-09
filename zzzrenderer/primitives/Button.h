//
// Created by ubuntu on 12/4/21.
//

#ifndef ANGINA_BUTTON_H
#define ANGINA_BUTTON_H

#include <cstdlib>

#include "renderer/primitives/Object.h"

struct Texture;
struct Point;
struct Rect;
struct InputEvent;
struct Renderer;

class Button: public Object {
public:
	Button(Texture&, Point, Dimensions);
};

#endif //ANGINA_BUTTON_H
