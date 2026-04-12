#include "SDLGPUTexture.h"

#include <cassert>

#include "SDL_render.h"

using namespace Backend::SDL::Resources;

SDLGPUTexture::SDLGPUTexture(SDL_Texture* t) noexcept: texture(t)
{
	assert(t);
}

SDLGPUTexture::~SDLGPUTexture() noexcept
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* SDLGPUTexture::get() const noexcept
{
	return texture;
}
