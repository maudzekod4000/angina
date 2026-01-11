#ifndef UI_SDL_WINDOW_H
#define UI_SDL_WINDOW_H

#include <memory>

#include "platform/ui/window/IWindow.h"
#include "platform/ui/window/WindowConfig.h"
#include "core/units/Units.hpp"
#include "core/error/Errors.h"

struct SDL_Window;

namespace Backend::SDL::UI {

class SDLWindow : public Platform::UI::IWindow {
	SDLWindow(SDL_Window*, const Platform::UI::WindowConfig&);
public:
	static std::unique_ptr<SDLWindow> make(const Platform::UI::WindowConfig&);

	Core::Errors::ErrorCode resize(Core::Units::Width w, Core::Units::Height h) override;
private:
	SDL_Window* window;
};

}

#endif // !UI_SDL_WINDOW_H
