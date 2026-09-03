#ifndef BACKEND_SDL_RENDERER_H
#define BACKEND_SDL_RENDERER_H

#include "backend/sdl/resources/SDLTexture.h"

struct SDL_Renderer;

namespace Backend::SDL::Rendering {
class SDLRenderer {
public:
	SDLRenderer(SDL_Renderer*);
	
	void render(Backend::SDL::Resources::SDLTexture);

	void clear();

	void present();

	SDL_Renderer* handle = nullptr; ///< Received from the outside but managed by this class.
};

}

#endif // !BACKEND_SDL_RENDERER_H
