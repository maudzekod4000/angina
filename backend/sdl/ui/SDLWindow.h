#ifndef UI_SDL_WINDOW_H
#define UI_SDL_WINDOW_H

#include <memory>
#include <expected>

#include "platform/ui/window/WindowConfig.h"
#include "core/units/Units.hpp"
#include "core/error/Errors.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Backend::SDL::UI {

class SDLWindow {
	SDLWindow(SDL_Window*);
public:
	SDLWindow() = default;
	static SDLWindow make(const Platform::UI::WindowConfig&, Core::Errors::ErrorCode&);

	void resize(Core::Units::Width w, Core::Units::Height h);

	SDL_Renderer* makeRenderer(Core::Errors::ErrorCode&);
private:
	SDL_Window* window = nullptr;
};

}

#endif // !UI_SDL_WINDOW_H
