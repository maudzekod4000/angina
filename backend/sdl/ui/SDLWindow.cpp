#include "SDLWindow.h"

#include "backend/sdl/error/SDLError.h"

#include "SDL.h"

using namespace Core::Errors;
using namespace Core::Units;
using namespace Platform::UI;
using namespace Backend::SDL::UI;

SDLWindow::SDLWindow(SDL_Window* w) : window(w) {}

SDLWindow SDLWindow::make(const WindowConfig& c, Core::Errors::ErrorCode& outErr)
{
	SDL_Window* window = SDL_CreateWindow(
		c.title.c_str(),
		c.xPos,
		c.yPos,
		c.width,
		c.height,
		SDL_WINDOW_SHOWN
	);
	if (!window) {
		outErr = Error::makeErr(ANGINA_CURRENT_FUNCTION);
	}

	return SDLWindow(window);
}

void SDLWindow::resize(Width w, Height h)
{
	SDL_SetWindowSize(window, w, h);
}

SDL_Renderer* SDLWindow::makeRenderer(Core::Errors::ErrorCode& err)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		err = Error::makeErr(ANGINA_CURRENT_FUNCTION);
	}

	return renderer;
}
