#ifndef ENGINEV2_GRAPHICS_SDL_RENDERER_SURFACERENDERERCOMPONENT_H_
#define ENGINEV2_GRAPHICS_SDL_RENDERER_SURFACERENDERERCOMPONENT_H_

struct SDL_Surface;
struct SDL_Rect;

class SurfaceRendererComponent {
public:

	void fillRect(SDL_Surface&) const;
	void drawOnSurface(SDL_Surface& src, SDL_Surface& dest) const;
	void drawOnSurface(SDL_Surface& srcImage, SDL_Rect& srcRectangle, SDL_Surface& destImage, SDL_Rect& destRectangle) const;

	// TODO: Test this once we have good abstraction around rect
	void drawOnSurfaceStretch(SDL_Surface& srcImage, SDL_Surface& destImage, SDL_Rect& stretchRect);
};

#endif /* ENGINEV2_GRAPHICS_SDL_RENDERER_SURFACERENDERERCOMPONENT_H_ */
