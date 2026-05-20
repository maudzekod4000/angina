#include <cstdint>
#include <cstdlib>

#include "engine_impl/sdl/SDLEngine.h"
#include "core/units/Units.hpp"
#include "core/error/Errors.h"

class MyTestEngine : public EngineImpl::SDL::SDLEngine {
public:
	explicit MyTestEngine(const Platform::UI::WindowConfig& config, Core::Units::RatePerSecond fps)
		: EngineImpl::SDL::SDLEngine(config, fps) {}
protected:
	Core::Errors::ErrorCode beforeStart() override {
		//texResLoader->load()
		return {};
	}
	Core::Errors::ErrorCode beforeUpdate() override { return {}; }
	Core::Errors::ErrorCode afterUpdate() override { return {}; }
	Core::Errors::ErrorCode beforeEnd() override { return {}; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Platform::UI::WindowConfig winConfig("Hi!", Core::Units::AbsX(100), Core::Units::AbsY(100), Core::Units::Width(640), Core::Units::Height(480));
	MyTestEngine eng(winConfig, Core::Units::RatePerSecond(60));

	if (const auto result = eng.start(); result) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
