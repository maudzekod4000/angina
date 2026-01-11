#include "SDLWindow.h"

#include "SDL.h"

using namespace Core::Errors;
using namespace Core::Units;
using namespace Platform::UI;
using namespace Backend::SDL::UI;

SDLWindow::SDLWindow(SDL_Window* w, const WindowConfig& c):
	IWindow(c), window(w) {}

std::unique_ptr<SDLWindow> SDLWindow::make(const WindowConfig& c)
{
	SDL_Window* window = SDL_CreateWindow(
		c.title.c_str(),
		c.xPos.value,
		c.yPos.value,
		c.width.value,
		c.height.value,
		SDL_WINDOW_SHOWN
	);
	if (!window) {
		return nullptr;
	}

	return std::unique_ptr<SDLWindow>(new SDLWindow(window, c));
}

ErrorCode SDLWindow::resize(Width w, Height h)
{
	SDL_SetWindowSize(window, w.value, h.value);
	return ErrorCode();
}
