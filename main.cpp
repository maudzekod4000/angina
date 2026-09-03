#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "engine_impl/sdl/SDLEngine.h"
#include "core/units/Units.hpp"
#include "core/error/Errors.h"
#include "resources/Resources.h"

class MyTestEngine : public EngineImpl::SDL::SDLEngine {
public:
	explicit MyTestEngine(const Platform::UI::WindowConfig& config, Core::Units::RatePerSecond fps)
		: EngineImpl::SDL::SDLEngine(config, fps) {}
protected:
	Core::Errors::ErrorCode beforeStart() override {
		// TODO: Hmmmm....so I wonder whether its better to have the size of an image
		// hardcoded in the codebase or dynamically fetched from the image file?
		// I think its better to have it dynamically read from the headers of the image.
		// And the client of the code could overwrite that in order to scale the image
		// which is not a great idea usually...
		std::vector<std::filesystem::path> resourcePaths;
		resourcePaths.push_back(::Resources::resource("engine/balls.png"));
		resourcePaths.push_back(::Resources::resource("engine/human.png"));
		const auto idsOrErrs = loadTextures(resourcePaths);

		for (const auto& idOrErr : idsOrErrs) {
			if (idOrErr.has_value()) {
				textureIds.push_back(idOrErr.value());
			}
			else {
				logger->log(Platform::Logging::Level::ERROR, idOrErr.error());
			}
		}

		return {};
	}
	Core::Errors::ErrorCode beforeUpdate() override { return {}; }
	Core::Errors::ErrorCode afterUpdate() override { return {}; }
	Core::Errors::ErrorCode beforeEnd() override { return {}; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Platform::UI::WindowConfig winConfig("Hi!", Core::Units::AbsX(100), Core::Units::AbsY(100), Core::Units::Width(255), Core::Units::Height(128));
	MyTestEngine eng(winConfig, Core::Units::RatePerSecond(60));

	if (const auto err = eng.start(); err) {
		std::cerr << std::string_view(err) /* TODO: Add a << operator to ErrorCode */ << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
