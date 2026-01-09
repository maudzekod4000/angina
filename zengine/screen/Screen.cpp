#include "engine/screen/Screen.h"

#include "renderer/drawable/Drawable.h"

Screen::Screen() {}

Screen& Screen::put(Drawable& drawable) {
	drawables.push_back(&drawable);
	return *this;
}

const std::vector<Drawable*>& Screen::getDrawables() {
	return drawables;
}
