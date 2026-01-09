#ifndef ENGINEV2_GRAPHICS_ANIMATION_SPRITE_H
#define ENGINEV2_GRAPHICS_ANIMATION_SPRITE_H

#include <memory>
#include <vector>
#include <cstdint>

#include "enginev2/graphics/sdl/primitives/Texture.h"
#include "enginev2/graphics/sdl/primitives/Rectangle.h"
#include "enginev2/graphics/models/Point.h"
#include "enginev2/components/ID.h"

class SpriteAnimator;
class TextureRendererComponent;

class Sprite {
public:
	friend class SpriteAnimator;
	friend class TextureRendererComponent;
	friend class GameObject;

	Sprite() = default;
	Sprite(std::shared_ptr<Texture>, const std::vector<Rectangle>&, uint64_t animationTime);
	Sprite(SDL_Texture*, const std::vector<Rectangle>&, uint64_t animationTime);
	Sprite(SDL_Texture*, uint32_t frameCount, uint64_t animationTime);
	Sprite(std::shared_ptr<Texture>, uint32_t frameCount, uint64_t animationTime);
	Sprite(std::shared_ptr<Texture>);

	ID id;
private:
	std::shared_ptr<Texture> atlas;
	std::vector<Rectangle> frames;
	uint64_t animationTime;
	uint8_t currentFrame;
	uint8_t frameWidth;

	std::vector<Rectangle> generateFrames(uint32_t frameCount);
};

#endif // !ENGINEV2_GRAPHICS_ANIMATION_SPRITE_H
