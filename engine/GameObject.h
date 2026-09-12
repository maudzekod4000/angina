#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "backend/sdl/resources/SDLTexture.h"
#include "core/units/Units.hpp"

namespace Angina::EngineV3 {
	struct SpriteAnim {

		SpriteAnim(Core::Units::Rect onlyFrame) : currentFrame(onlyFrame) {}

		SpriteAnim(std::vector<Core::Units::Rect> frames, float animDuration) :
			currentFrame(), frames(std::move(frames)), animDuration(animDuration) {}


		// We need:
		// 1. a way to start the animation
		// 2. a way to reset the animation
		// 3. a way to stop the animation

		void update() {
			if (frames.empty()) return; // This is a single frame sprite, i.e. a normal texture.

			// TODO: Do some calculations to figure out the current frame based on the time that passed
			// between starting the animation and now.
		}

		// Design:
		// we need to track when the animation started and how long it has been running
		// in order to figure out which frame to show in the case of multiple frames.
		// if there is just a single frame then we just show that frame.

		// We can create another constructor that will just set a single frame and will not deal
		// with any time management.

		// another important thing is that we need to be able to stop the animation.

		Core::Units::Rect currentFrame;
	private:
		std::vector<Core::Units::Rect> frames;
		float animDuration = 0.0f;
	};

	struct GameObject {
		Backend::SDL::Resources::SDLTexture texture;
		int x, y, w, h;

		// TODO: To be honest, the game object should have a width and height...
		// semantically its more important that leaving the texture to determine the width and height of the 
		// game object...While we are just doing rendering this the current state is ok,
		// but when we start talking collisions we will be in a different ballgame.
	};
}

#endif // !ENGINE_GAME_OBJECT_H
