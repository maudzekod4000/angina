#include <cstdint>
#include <cstdlib>

#include "engine_impl/sdl/SDLEngine.h"
#include "core/units/Units.hpp"

class MyTestEngine : public EngineImpl::SDL::SDLEngine {
public:
	explicit MyTestEngine(const Platform::UI::WindowConfig& config, Core::Units::RatePerSecond fps)
		: EngineImpl::SDL::SDLEngine(config, fps) {}
protected:
	int beforeStart() override { return 0; }
	int beforeUpdate() override { return 0; }
	int afterUpdate() override { return 0; }
	int beforeEnd() override { return 0; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Platform::UI::WindowConfig winConfig("Hi!", Core::Units::AbsX(100), Core::Units::AbsY(100), Core::Units::Width(640), Core::Units::Height(480));
	MyTestEngine eng(winConfig, Core::Units::RatePerSecond(60));
	eng.start();

	return EXIT_SUCCESS;
}
