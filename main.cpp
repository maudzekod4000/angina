#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "engine_impl/sdl/SDLEngine.h"
#include "engine/Engine.h"
#include "core/units/Units.hpp"
#include "core/error/Errors.h"
#include "resources/Resources.h"

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Platform::UI::WindowConfig winConfig("Hi!", Core::Units::AbsX(100), Core::Units::AbsY(100), Core::Units::Width(255), Core::Units::Height(128));
	Angina::EngineV3::Engine eng(winConfig, Core::Units::RatePerSecond(60));

	if (const auto err = eng.start(); err) {
		std::cerr << std::string_view(err) /* TODO: Add a << operator to ErrorCode */ << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
