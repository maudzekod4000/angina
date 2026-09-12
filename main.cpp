#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "engine/Engine.h"
#include "core/units/Units.hpp"
#include "core/error/Errors.h"
#include "resources/Resources.h"

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Core::Errors::ErrorCode err;
	Platform::UI::WindowConfig winConfig("Hi!", Core::Units::AbsX(100), Core::Units::AbsY(100), Core::Units::Width(640), Core::Units::Height(480));
	Angina::EngineV3::Engine eng = Angina::EngineV3::Engine::make(winConfig, Core::Units::RatePerSecond(60), err);

	if (err) {
		std::cerr << std::string_view(err) << '\n';
		return EXIT_FAILURE;
	}

	if (err = eng.start(); err) {
		std::cerr << std::string_view(err) /* TODO: Add a << operator to ErrorCode */ << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
