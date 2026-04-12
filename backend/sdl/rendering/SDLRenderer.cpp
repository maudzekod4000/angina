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

void SDLRenderer::render(Platform::Resources::GPUTextureHandle tex)
{
	// Ok...so the handle contains a generic pointer to a structure of some sort.
	// what is the best way to cast it and check whether the cast is success...
	// As we are certain that the type will be an SDL texture
	SDLGPUTexture* sdlTexWrapper = static_cast<SDLGPUTexture*>(tex.ptr);

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

std::expected<GPUTextureHandle, ErrorCode> SDLRenderer::convertCPUToGPUTexture(CPUTextureHandle cpuTex)
{
	SDLCPUTexture* sdlTexWrapper = static_cast<SDLCPUTexture*>(cpuTex.ptr);
	SDL_Surface* sdlSurface = sdlTexWrapper->get();
	assert(sdlSurface);
	
	SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(renderer, sdlSurface);

	if (!sdlTex) {
		return std::unexpected(ErrorCode(-1, "Failed to convert CPU to GPU texture (SDL)"));
	}

	GPUTextureHandle handle{};
	handle.ptr = new SDLGPUTexture(sdlTex);
	handle.isReady = true;

	return handle;
}
