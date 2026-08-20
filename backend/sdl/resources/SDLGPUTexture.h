#ifndef RESOURCES_SDL_GPU_TEXTURE_H
#define RESOURCES_SDL_GPU_TEXTURE_H

#include "platform/resources/Texture.h"

struct SDL_Texture;

namespace Backend::SDL::Resources {
// Wrapper around SDL_Texture, which is a texture in GPU memory. Manages the lifetime of a SDL_Texture.
// This wrapper could be used to store metadata about the image.
class SDLGPUTexture : public Platform::Resources::Texture {
public:

	/// @param s Non-null. Check for null before passing, the class relies on non-null pointer. Takes ownership of the memory.
	explicit SDLGPUTexture(SDL_Texture* t) noexcept;

	~SDLGPUTexture() noexcept;

	SDL_Texture* get() const noexcept;

	int width() const override;

	int height() const override;
private:
	SDL_Texture* texture;

	// TODO: At some point I might ditch the inheritance and just
	// have a concrete implementation of the engine
	// But let's not overhaul everything at once.
	int texWidth = 0;
	int texHeight = 0;
};
}

#endif // !RESOURCES_SDL_GPU_TEXTURE_H
