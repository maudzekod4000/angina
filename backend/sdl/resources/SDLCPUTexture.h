#ifndef SDL_RESOURCES_SDLCPUTEXTURE_H
#define SDL_RESOURCES_SDLCPUTEXTURE_H

#include "platform/resources/CPUTexture.h"

struct SDL_Surface;

namespace Backend::SDL::Resources {

// Wrapper around SDL_Surface, which is a texture in main memory. Manages the lifetime of a SDL_Surface.
// This wrapper could be used to store metadata about the image.
class SDLCPUTexture : public Platform::Resources::CPUTexture {
public:

	/// @param s Non-null. Check for null before passing, the class relies on non-null pointer. Takes ownership of the memory.
	explicit SDLCPUTexture(SDL_Surface* s) noexcept;

	~SDLCPUTexture() noexcept;

	SDL_Surface* get() const noexcept;
private:
	SDL_Surface* texture;
};
}

#endif // !SDL_RESOURCES_SDLCPUTEXTURE_H
