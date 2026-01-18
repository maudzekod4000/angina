#ifndef SDL_RESOURCES_SDLCPUTEXTURE_H
#define SDL_RESOURCES_SDLCPUTEXTURE_H

#include <cassert>

#include "platform/resources/CPUTexture.h"
#include "SDL_surface.h"

namespace Backend::SDL::Resources {

// Wrapper around SDL_Surface, which is a texture in main memory. Manages the lifetime of a SDL_Surface.
// This wrapper could be used to store metadata about the image.
class SDLCPUTexture : public Platform::Resources::CPUTexture {
public:

	/// @param s Non-null. Check for null before passing, the class relies on non-null pointer. Takes ownership of the memory.
	explicit SDLCPUTexture(SDL_Surface* s) noexcept: texture(s) {
		assert(s);
	}

	~SDLCPUTexture() noexcept {
		SDL_FreeSurface(texture);
	}

	const SDL_Surface* const get() const noexcept {
		return texture;
	}
private:
	SDL_Surface* texture; ///< Read-only pointer to the CPU texture. Do not delete.
};
}

#endif // !SDL_RESOURCES_SDLCPUTEXTURE_H
