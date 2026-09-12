#include "SDLRenderer.h"

#include <cassert>

#include "SDL_render.h"

using namespace Backend::SDL::Rendering;
using namespace Backend::SDL::Resources;

SDLRenderer::SDLRenderer(SDL_Renderer* r): handle(r) {}

void SDLRenderer::render(SDLTexture texture, int viewportOffX, int viewportOffY, int renderWidth, int renderHeight,
	int texOffX, int texOffY, int texCropW, int texCropH)
{
	assert(texture.handle);
	SDL_Rect dstRect{ viewportOffX, viewportOffY, renderWidth, renderHeight };
	SDL_Rect srcRect{ texOffX, texOffY, texCropW, texCropH };

	const int res = SDL_RenderCopy(handle, texture.handle, &srcRect, &dstRect);

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
