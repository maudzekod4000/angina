#ifndef SDL_RESOURCES_SDLCPUTEXTURE_H
#define SDL_RESOURCES_SDLCPUTEXTURE_H

#include "platform/resources/CPUTexture.h"
#include "SDL_surface.h"

namespace Backend::SDL::Resources {

// Wrapper around SDL_Surface, which is a texture in main memory.
// This wrapper could be used to store metadata about the image...currently it seems useless but lets see.
class SDLCPUTexture : public Platform::Resources::CPUTexture {
public:
	explicit SDLCPUTexture(SDL_Surface* s) noexcept: texture(s) {}

	const SDL_Surface* const get() const noexcept {
		return texture;
	}
private:
	SDL_Surface* texture; ///< Read-only pointer to the CPU texture. Do not delete.
};
}

#endif // !SDL_RESOURCES_SDLCPUTEXTURE_H
