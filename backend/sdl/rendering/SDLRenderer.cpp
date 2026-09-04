#include "SDLRenderer.h"

#include <cassert>

#include "SDL_render.h"

using namespace Backend::SDL::Rendering;
using namespace Backend::SDL::Resources;

SDLRenderer::SDLRenderer(SDL_Renderer* r): handle(r) {}

void SDLRenderer::render(SDLTexture texture)
{
	assert(texture.handle);
	const int res = SDL_RenderCopy(handle, texture.handle, NULL, NULL);

	assert(res == 0);
}

void SDLRenderer::clear()
{
	const int res = SDL_RenderClear(handle);
	assert(res == 0);
}

void SDLRenderer::present()
{
	SDL_RenderPresent(handle);
}
