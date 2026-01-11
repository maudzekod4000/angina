#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include "engine/Engine.h"
#include "backend/sdl/init/SDLVideoLifecycleManager.h"
#include "platform/logging/ConsoleLogger.h"
#include "backend/sdl/ui/SDLWindow.h"
#include "backend/sdl/input/SDLInputEventManager.h"
#include "core/units/Units.hpp"

class MyTestEngine : public Angina::EngineV3::Engine {
public:
	explicit MyTestEngine(
		Platform::Init::SubsystemLifecycleManagersPtr slms,
		Platform::Logging::LoggerPtr logger,
		Platform::UI::WindowPtr window,
		Platform::Input::InputEventManagerPtr eventMgr
	):
		Angina::EngineV3::Engine(std::move(slms), std::move(logger), std::move(window), std::move(eventMgr), Core::Units::RatePerSecond(60)) {}
protected:
	int beforeStart() override { return 0; }
	int beforeUpdate() override { return 0; }
	int afterUpdate() override { return 0; }
	int beforeEnd() override { return 0; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Platform::Logging::LoggerPtr log = std::make_unique<Platform::Logging::ConsoleLogger>();
	
	std::vector<std::shared_ptr<Platform::Init::ISubsystemLifecycleManager>> slmsVec;
	slmsVec.push_back(std::make_shared<Backend::SDL::Init::SDLVideoLifecycleManager>());
	auto slms = std::make_unique<Platform::Init::SubsystemLifecycleManagers>(slmsVec);
	Platform::UI::WindowConfig winConfig("Hi!", Core::Units::AbsX(100), Core::Units::AbsY(100), Core::Units::Width(640), Core::Units::Height(480));
	Platform::UI::WindowPtr window = Backend::SDL::UI::SDLWindow::make(winConfig);
	Platform::Input::InputEventManagerPtr evMgr = Backend::SDL::Input::SDLInputEventManager::make();
	
	MyTestEngine eng(std::move(slms), std::move(log), std::move(window), std::move(evMgr));
	eng.start();

	return EXIT_SUCCESS;
}
