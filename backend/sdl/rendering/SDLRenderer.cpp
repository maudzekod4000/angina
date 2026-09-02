#include "SDLRenderer.h"

#include <cassert>
#include <iostream>

#include "SDL_render.h"

#include "backend/sdl/error/SDLError.h"
#include "sdl/resources/SDLGPUTexture.h"
#include "sdl/resources/SDLCPUTexture.h"

using namespace Backend::SDL::Rendering;
using namespace Backend::SDL::Resources;
using namespace Platform::Resources;
using namespace Core::Errors;

SDLRenderer::SDLRenderer(SDL_Renderer* r): renderer(r) {}

std::shared_ptr<SDLRenderer> SDLRenderer::makeShared(SDL_Renderer* r)
{
	return std::shared_ptr<SDLRenderer>(new SDLRenderer(r));
}

void SDLRenderer::render(Platform::Resources::TextureHandle tex)
{
	assert(dynamic_cast<SDLGPUTexture*>(tex.ptr));

	SDLGPUTexture* sdlTexWrapper = static_cast<SDLGPUTexture*>(tex.ptr);

	SDL_Texture* sdlTex = sdlTexWrapper->get();

	assert(sdlTex);
	const int res = SDL_RenderCopy(renderer, sdlTex, NULL, NULL);

	assert(res == 0);
}

void SDLRenderer::clear()
{
	const int res = SDL_RenderClear(renderer);
	assert(res == 0);
}

void SDLRenderer::present()
{
	SDL_RenderPresent(renderer);
}

std::expected<TextureHandle, ErrorCode> SDLRenderer::transferGPU(TextureHandle cpuTex)
{
	assert(dynamic_cast<SDLCPUTexture*>(cpuTex.ptr));
	SDLCPUTexture* sdlTexWrapper = static_cast<SDLCPUTexture*>(cpuTex.ptr);

	SDL_Surface* sdlSurface = sdlTexWrapper->get();

	assert(sdlSurface);

	SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(renderer, sdlSurface);

	if (!sdlTex) {
		return std::unexpected(Backend::SDL::Error::makeErr(ANGINA_CURRENT_FUNCTION));
	}

	auto gpuTex = new SDLGPUTexture(sdlTex);

	std::cout << "The width of the texture is: " << gpuTex->width() << std::endl;

	return TextureHandle(gpuTex);
}
