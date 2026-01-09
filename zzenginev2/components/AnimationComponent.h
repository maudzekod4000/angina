#ifndef ENGINEV2_COMPONENTS_ANIMATIONCOMPONENT_H_
#define ENGINEV2_COMPONENTS_ANIMATIONCOMPONENT_H_

#include <cstdint>
#include <vector>

#include "enginev2/graphics/sdl/primitives/Rectangle.h"

class Texture;

/**
 * This assumes that the animation is 1 second long.
 */
class AnimationComponent {
public:
	AnimationComponent();

	void init(Texture&, int32_t frames, int32_t frameRate);

	void addFrame(const Rectangle&);
	void update();
private:
	Texture* tx;
	std::vector<Rectangle> frames;
	int32_t frameCount;
	int32_t index;
	int32_t framesPerUpdate;
	int32_t currentFrame;
};

#endif /* ENGINEV2_COMPONENTS_ANIMATIONCOMPONENT_H_ */
