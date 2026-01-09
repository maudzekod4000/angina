#ifndef SDL_COMPONENTS_WINDOW_H_
#define SDL_COMPONENTS_WINDOW_H_

#include <string>

#include "SDL_pixels.h"

#include "enginev2/graphics/models/Width.h"
#include "enginev2/graphics/models/Height.h"

struct SDL_Window;
struct SDL_Surface;
struct Color;
class Renderer;

/**
 * Wrapper around SDL_Window.
 * Manages initialization and destruction of window and it's surface.
 */
class Window {
public:
	friend class Renderer;
	friend class TextureRendererComponent;

	Window();
	~Window();

	void init(const std::string& title,
			int32_t xPos,
			int32_t yPos,
			Width width,
			Height height);

	void init(const std::string& title,
				Width width,
				Height height);

	void resize(Width width, Height height);
	void update();
	void clear();
	void setClearColor(const Color&);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;
private:
	SDL_Color clearColor;
	SDL_Window* sdlWindow;
	SDL_Surface* surface;
};

#endif /* SDL_COMPONENTS_WINDOW_H_ */
