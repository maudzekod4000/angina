#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "backend/sdl/resources/SDLTexture.h"

namespace Angina::EngineV3 {
	struct GameObject {
		// TODO: Think: Maybe the texture can be in the Animation struct?
		Backend::SDL::Resources::SDLTexture texture;
		int w, h;
		int flip = 0; // See SDL_RendererFlip

		// TODO: To be honest, the game object should have a width and height...
		// semantically its more important that leaving the texture to determine the width and height of the 
		// game object...While we are just doing rendering this the current state is ok,
		// but when we start talking collisions we will be in a different ballgame.
	};
}

#endif // !ENGINE_GAME_OBJECT_H
