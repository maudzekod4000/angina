#ifndef SDL_COMPONENTS_SURFACE_H_
#define SDL_COMPONENTS_SURFACE_H_

#include <string>

struct SDL_Surface;
class GameEngine;

/**
 * Wrapper around SDL_Surface and manages the life-cycle of it.
 */
class Surface {
public:
	friend class GameEngine;

	Surface(const std::string& surfaceAssetPath);
	Surface(SDL_Surface* rawSurface);
	~Surface();
private:
	SDL_Surface* surface;
};

#endif /* SDL_COMPONENTS_SURFACE_H_ */
