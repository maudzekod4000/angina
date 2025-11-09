#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "SDL.h"

#include "enginev2/graphics/sdl/init/Graphics.h"
#include "enginev2/graphics/sdl/window/Window.h"
#include "enginev2/graphics/sdl/primitives/Surface.h"
#include "enginev2/graphics/models/Width.h"
#include "enginev2/graphics/models/Height.h"
#include "enginev2/graphics/models/Point.h"
#include "enginev2/graphics/sdl/renderer/SurfaceRendererComponent.h"
#include "examples/SkeletalRainOfBlood/Game.h"
#include "resources/Resources.h"

#include "exceptions/BaseException.h"

#undef main

// Plan for action.
// 1. Create a enginev3 version and let's implement the logic for an engine from scratch.
// 2. Think about abstract actions that will be needed to implement the chess but are not concrete to chess.
// 3. First step would be just to render a texture.
int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	try {
		Graphics g;
		g.init();
		Game game;

		game.start();
	} catch (const BaseException &ex) {
		std::cerr << ex << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
