#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "SDL.h"

#include "examples/chess/ChessGame.h"
#include "exceptions/BaseException.h"

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	try {
		ChessGame game;
		game.start();
	} catch (const BaseException &ex) {
		std::cerr << ex << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
