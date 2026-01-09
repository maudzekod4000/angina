#ifndef SDL_GRAPHICS_TEXTURE_H_
#define SDL_GRAPHICS_TEXTURE_H_

#include "enginev2/graphics/models/Dimensions.h"
#include "enginev2/graphics/sdl/primitives/Rectangle.h"
#include "enginev2/components/ID.h"

#include "SDL_render.h"

struct SDL_Point;
struct SDL_Texture;
class TextureRendererComponent;

class Texture {
public:
	friend class TextureRendererComponent;

	Texture(SDL_Texture*);
	~Texture();

	void modulateColor(const Color&) const;
	void activateBlend() const;
	void setAlpha(uint8_t value) const;

	/// <summary>
	/// Use negative angles for counterclockwise rotation.
	/// </summary>
	void rotate(double angle);
	void activateHFlip();
	void activateVFlip();

	Dimensions getDimensions() const;

	ID id;
private:
	Dimensions dim;
	SDL_Texture* texture;
	float rotation;
	SDL_RendererFlip flip;
};

#endif /* SDL_GRAPHICS_TEXTURE_H_ */
