#include "SDLCPUTexture.h"

#include <cassert>

#include "SDL_surface.h"

using namespace Backend::SDL::Resources;

SDLCPUTexture::SDLCPUTexture(SDL_Surface* s) noexcept: texture(s) {
	assert(s);
}

SDLCPUTexture::~SDLCPUTexture() noexcept {
	SDL_FreeSurface(texture);
}

const SDL_Surface* const SDLCPUTexture::get() const noexcept {
	return texture;
}
