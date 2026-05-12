#include "SDLRenderer.h"
#include "SDLRenderer.h"

#include <cassert>

#include "SDL_render.h"

#include "sdl/resources/SDLGPUTexture.h"
#include "sdl/resources/SDLCPUTexture.h"

using namespace Backend::SDL::Rendering;
using namespace Backend::SDL::Resources;
using namespace Platform::Resources;
using namespace Core::Errors;

SDLRenderer::SDLRenderer(SDL_Renderer* r): renderer(r) {}

std::unique_ptr<SDLRenderer> SDLRenderer::make(SDL_Renderer* r)
{
	return std::unique_ptr<SDLRenderer>(new SDLRenderer(r));
}

std::shared_ptr<SDLRenderer> SDLRenderer::makeShared(SDL_Renderer* r)
{
	return std::shared_ptr<SDLRenderer>(new SDLRenderer(r));
}

void SDLRenderer::render(Platform::Resources::TextureHandle tex)
{
	SDLGPUTexture* sdlTexWrapper = dynamic_cast<SDLGPUTexture*>(tex.ptr);
	if (!sdlTexWrapper) {
		assert(false && "render: expected SDLGPUTexture");
		return;
	}

	auto sdlTex = sdlTexWrapper->get();

	// There should be another part of the system which makes sure all the pointers
	// are valid when they reach this point...
	const int res = SDL_RenderCopy(renderer, sdlTex, NULL, NULL);

	// Even if the result is non-zero....what ? we can't keep printing errors all the time.
	// It will be a mess...But still it's not a bad idea to have some logging
	// I think it's useful to have a logger which can deduplicate errors
	// This scenario happened on the Arena project too and it would be useful even now.

	assert(res == 0);
}


// So there should be a class that is a texture loader.
// it should have a reference to the CPU texture loader and
// a reference to the converter...
// Now that's a bit shitty because that means that we should always convert,....
// but it could be made in a way that does not require this or maybe the 
// converter will be a noop? hmmmm

// Lets think of the usual flow of things:
// 1. We load the textures into main memory in parallel (whatever)
// 2. We need a way to transfer them to GPU and delete the CPU resources...
// 3. We need a way to reference the GPU resources by Id.....
// It would be good to reuse the Id from the CPU loading.
// So that could be a class that does all those things.

std::expected<TextureHandle, ErrorCode> SDLRenderer::convertCPUToGPUTexture(TextureHandle cpuTex)
{
	SDLCPUTexture* sdlTexWrapper = dynamic_cast<SDLCPUTexture*>(cpuTex.ptr);
	if (!sdlTexWrapper) {
		return std::unexpected(ErrorCode(-1, "convertCPUToGPUTexture: expected SDLCPUTexture", ANGINA_CURRENT_FUNCTION));
	}

	SDL_Surface* sdlSurface = sdlTexWrapper->get();
	
	SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(renderer, sdlSurface);

	if (!sdlTex) {
		return std::unexpected(ErrorCode(-1, "Failed to convert CPU to GPU texture (SDL)", ANGINA_CURRENT_FUNCTION));
	}

	TextureHandle handle{};
	handle.ptr = new SDLGPUTexture(sdlTex);


	return handle;
}
