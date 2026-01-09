#include "Dimensions.h"

Dimensions::Dimensions() :
		w(0), h(0) {
}
Dimensions::Dimensions(float width, float height) :
		w(width), h(height) {
}

const Dimensions Dimensions::UNDEFINED(0, 0);
