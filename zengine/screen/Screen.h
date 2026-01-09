#ifndef SDL_ENGINE_PAGE_PAGE_H_
#define SDL_ENGINE_PAGE_PAGE_H_

#include <vector>

struct Drawable;

/**
 * Class that represents a full screen page.
 * It is a container for objects, rectangles, etc. and provides a way to add and get these primitives for drawing.
 *
 * Does not handle resource destruction.
 */
class Screen {
public:
	Screen();

	Screen& put(Drawable& drawable);

	const std::vector<Drawable*>& getDrawables();
private:
	std::vector<Drawable*> drawables;
};

#endif /* SDL_ENGINE_PAGE_PAGE_H_ */
