#ifndef SDL_GRAPHICS_RENDERER_H_
#define SDL_GRAPHICS_RENDERER_H_

#include <vector>

#include "renderer/primitives/Dimensions.h"
#include "renderer/primitives/Point.h"

struct SDL_Renderer;
struct Texture;
struct Rect;
struct Window;
struct Object;
struct Surface;
struct Button;

class Renderer {
public:
	Renderer(Window&);
	~Renderer();

	void clear();
	void render(const Texture&) const;
	void render(Rect&) const;
	void render(Object&) const;
	void update();

	Texture* from(Surface&) const;
	std::vector<Texture*> from(const std::vector<Surface*>&) const;
	Object* from(Texture&, Point, Dimensions) const;
	Object* fromSurface(Surface&, Point, Dimensions) const;
	Button* from(Texture&);
private:
	void init(Window&);
	void deinit();

	SDL_Renderer *renderer;
};

#endif /* SDL_GRAPHICS_RENDERER_H_ */
