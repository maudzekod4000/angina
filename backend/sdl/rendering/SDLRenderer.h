#ifndef BACKEND_SDL_RENDERER_H
#define BACKEND_SDL_RENDERER_H

#include "backend/sdl/resources/SDLTexture.h"
#include "core/units/Units.hpp"

struct SDL_Renderer;

namespace Backend::SDL::Rendering {
class SDLRenderer {
public:
	SDLRenderer(SDL_Renderer*);
	SDLRenderer() = default;

	void render(Backend::SDL::Resources::SDLTexture, int viewportOffX, int viewportOffY, int renderWidth, int renderHeight,
		int texOffX, int texOffY, int texCropW, int texCropH, int flip /* see SDL_RendererFlip */);

	void clear();

	void present();

	SDL_Renderer* handle = nullptr; ///< Received from the outside but managed by this class.
};

}

#endif // !BACKEND_SDL_RENDERER_H
