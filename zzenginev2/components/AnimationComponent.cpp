#include "AnimationComponent.h"

#include "enginev2/graphics/sdl/primitives/Texture.h"

AnimationComponent::AnimationComponent(): tx(nullptr), frameCount(0), index(0), framesPerUpdate(0), currentFrame(0) {}

void AnimationComponent::init(Texture& texture, int32_t frames, int32_t frameRate) {
    tx = &texture;
    frameCount = frames;
    framesPerUpdate = frameRate / frameCount;
}

void AnimationComponent::addFrame(const Rectangle& rect) {
	if (index >= frameCount - 1) return;

	frames.push_back(rect);
}

void AnimationComponent::update() {
  if (currentFrame == framesPerUpdate) {
      //tx->setClip(frames[index++]);
      currentFrame = 0;
  } else {
      currentFrame++;
  }

	if (index >= frameCount - 1) {
		index = 0;
	}
}
