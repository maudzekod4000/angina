#include "SDLTexture.h"

#include <assert.h>

#include "SDL_render.h"

using namespace Backend::SDL::Resources;

SDLTexture::SDLTexture(SDL_Texture* t): tex(t)
{
	assert(t);
	SDL_QueryTexture(t, NULL, NULL, &width, &height);
}

void SDLTexture::freeMem()
{
	SDL_DestroyTexture(tex);
}
