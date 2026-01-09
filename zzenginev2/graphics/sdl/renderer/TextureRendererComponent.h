#ifndef ENGINEV2_GRAPHICS_SDL_RENDERER_TEXTURERENDERERCOMPONENT_H_
#define ENGINEV2_GRAPHICS_SDL_RENDERER_TEXTURERENDERERCOMPONENT_H_

#include "enginev2/graphics/models/Color.h"

class Window;
class Texture;
class Rectangle;
class Pixel;
class Line;
class GameObject;
class Sprite;

struct SDL_Renderer;

class TextureRendererComponent {
public:
	~TextureRendererComponent();

	void init(Window&, const Color& clearColor);

	void clear();
	void render(Texture&);
	void render(GameObject&);
	void render(Texture&, Rectangle& viewPort);
	void render(Rectangle&);
	void render(Pixel&);
	void render(Line&);
	void render(Sprite&);
	void update();
	SDL_Renderer* get() const;

	void setClearColor(const Color&);
private:
	Color clearColor;
	SDL_Renderer* renderer;
};

#endif /* ENGINEV2_GRAPHICS_SDL_RENDERER_TEXTURERENDERERCOMPONENT_H_ */
