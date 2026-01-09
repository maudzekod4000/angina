#ifndef ENGINEV2_GRAPHICS_ANIMATION_SPRITE_ANIMATOR_H
#define ENGINEV2_GRAPHICS_ANIMATION_SPRITE_ANIMATOR_H

#include <memory>
#include <unordered_map>
#include <cstdint>

#include "enginev2/graphics/sdl/primitives/Texture.h"
#include "enginev2/graphics/animation/Sprite.h"
#include "platform/ids/ForwardIdGenerator.h"
#include "enginev2/components/PrimitivesStorage.h"

class GameEngine;

static struct AnimatedSprite {
	AnimatedSprite() = default;

	Sprite* sprite;
	uint64_t timeSinceAnimationStart; // TODO: Consider switching this to chrono::duration
	bool isActive;
};

class SpriteAnimator : public PrimitivesStorage<Sprite> {
public:
	friend class GameEngine;

	ID add(Sprite&);
	Sprite& addAndGet(Sprite&);
	void updateSprite(ID, std::shared_ptr<Texture>);
	void activate(ID);
	void deactivate(ID);
	void remove(ID);
	void update();
private:
	ForwardIdGenerator idGen;
	std::unordered_map<ID, AnimatedSprite> animatedSprites;
	
	void process(AnimatedSprite&);
};

#endif // !ENGINEV2_GRAPHICS_ANIMATION_SPRITE_ANIMATOR_H
