#ifndef UI_SDL_WINDOW_H
#define UI_SDL_WINDOW_H

import errors;

#include <memory>

#include "ui/window/IWindow.h"
#include "ui/window/WindowConfig.h"
#include "core/units/Units.hpp"

struct SDL_Window;

namespace Angina::UI {

class SDLWindow : public IWindow {
	SDLWindow(SDL_Window*, const WindowConfig&);
public:
	static std::unique_ptr<SDLWindow> make(const WindowConfig&);

	Errors::ErrorCode resize(Units::Width w, Units::Height h) override;
private:
	SDL_Window* window;
};

}

#endif // !UI_SDL_WINDOW_H
