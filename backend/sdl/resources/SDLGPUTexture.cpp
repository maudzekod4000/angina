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

const SDL_Texture* const SDLGPUTexture::get() const noexcept
{
	return texture;
}
