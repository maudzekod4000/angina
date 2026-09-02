#ifndef BACKEND_SDL_RESOURCES_SDLTEXTURE_H
#define BACKEND_SDL_RESOURCES_SDLTEXTURE_H

struct SDL_Texture;

namespace Backend::SDL::Resources {
	struct SDLTexture {
		SDLTexture() = default;
		SDLTexture(SDL_Texture*);

		void freeMem();

		SDL_Texture* tex = nullptr;
		int width = 0;
		int height = 0;
	};
}

#endif // !BACKEND_SDL_RESOURCES_SDLTEXTURE_H