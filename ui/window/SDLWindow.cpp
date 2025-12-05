#include "SDLWindow.h"

#include "SDL.h"

using namespace Angina::UI;
using namespace Angina::Errors;
using namespace Angina::Units;

SDLWindow::SDLWindow(SDL_Window* w, const WindowConfig& c):
	BaseWindow(c), window(w) {}

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

	return std::make_unique<SDLWindow>(window, c);
}

ErrorCode SDLWindow::resize(Width w, Height h)
{
	SDL_SetWindowSize(window, w.value, h.value);
}
