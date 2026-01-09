#include "Color.h"

const Color Color::NONE;
const Color Color::RED ( 255, 0, 0, 255 );
const Color Color::GREEN ( 0, 255, 0, 255 );
const Color Color::BLUE ( 0, 0, 255, 255 );
const Color Color::BLACK ( 0, 0, 0, 255 );

Color::Color(): Color(0, 0, 0, 0) {}
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a): red(r), green(g), blue(b), alpha(a) {}
Color::Color(uint8_t r, uint8_t g, uint8_t b) : Color(r, g, b, 255) {}
