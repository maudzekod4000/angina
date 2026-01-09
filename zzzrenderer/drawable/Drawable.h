#ifndef RENDERER_DRAWABLE_DRAWABLE_H_
#define RENDERER_DRAWABLE_DRAWABLE_H_

struct Renderer;

class Drawable {
public:
	virtual ~Drawable() = default;

	virtual void draw(Renderer&) = 0;
};

#endif /* RENDERER_DRAWABLE_DRAWABLE_H_ */
