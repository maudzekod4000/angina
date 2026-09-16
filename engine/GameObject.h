#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include <chrono>

#include "backend/sdl/resources/SDLTexture.h"
#include "core/time/Stopwatch.h"

namespace Angina::EngineV3 {

	// TODO: I never created such a class so its a bit weird
	// but i think the idea is that every object might have a movement
	// associated with it.
	// the movement will have a destination and a starting point
	// ( i am omitting collisions for now haha)
	// sooo every movement will have a speed (a bit naieve because what about different terrains)
	// the good thing is that we can iterate only these Movement objects to figure out 
	// the next step in the movement.
	// on 'update' we will interpolate between the start and destination points
	// but here again we also depend on the time...sooo for example
	// what would be the speed of the object? in pixels? some arbitrary unit?
	// If there is some metric system used at some point we can convert the pixels 
	// to meters hahahah, but wait........what if the resolution changes....
	// then the movement will be different....we have to keep the scale of things
	// even if the resolution changes.
	// well we will use a fixed resolution for starters.
	// Hmmm so it turns out that accessing several vectors at once is very cache friendly.
	struct Movement {

		void start(int destX, int destY, int movSpeed) {
			destinationX = destX;
			destinationY = destY;
			speed = movSpeed;
			clock.reset();
		}

		void stop() {
			speed = 0;
		}

		// This will advance the movement to the next step based on the passed time.
		void update() {
			if (speed == 0) return;

			long long timeSinceStartMs = std::chrono::duration_cast<std::chrono::milliseconds>(clock.elapsed()).count();


		}

		int posX = 0, posY = 0; // These are the GameObject positions.
	private:
		int destinationX = 0, destinationY = 0;
		int speed = 0; // Pixels per 1000 ms
		Core::Time::Stopwatch clock;
	};

	struct Animation {

		Animation(int frameCount): frameCount(frameCount) {}
		
		// TODO: THink: Hmmm i think this kinda time interpolation
		// and the kind that will be used for movement might share similar properties
		// but lets see...

		// Having the animation duration here allows us to change up the 
		// animation speed without creating a new Animation
		void start(int animDurMs) {
			durationMs = animDurMs;
			clock.reset();
		}

		void stop() {
			durationMs = 0;
		}

		void update() {
			if (durationMs == 0 || frameCount == 1) return;

			long long timeSinceStartMs = std::chrono::duration_cast<std::chrono::milliseconds>(clock.elapsed()).count();

			float animProgressPercent = timeSinceStartMs / float(durationMs);
			float animPercentNormalized = animProgressPercent - int(animProgressPercent);
			currentFrameIdx = int(frameCount * animPercentNormalized);
		}

		int currentFrameIdx = 0;
	private:
		int frameCount = 0;
		int durationMs = 0;
		Core::Time::Stopwatch clock;
	};

	struct GameObject {
		// TODO: Think: Maybe the texture can be in the Animation struct?
		Backend::SDL::Resources::SDLTexture texture;
		int x, y, w, h;

		// TODO: To be honest, the game object should have a width and height...
		// semantically its more important that leaving the texture to determine the width and height of the 
		// game object...While we are just doing rendering this the current state is ok,
		// but when we start talking collisions we will be in a different ballgame.
	};
}

#endif // !ENGINE_GAME_OBJECT_H
