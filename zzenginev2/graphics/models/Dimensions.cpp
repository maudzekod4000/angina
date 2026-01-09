#include "Dimensions.h"

Dimensions::Dimensions(): w(0), h(0) {}
Dimensions::Dimensions(uint16_t width, uint16_t height): w(width), h(height) {}

const Dimensions Dimensions::UNDEFINED(0, 0);
