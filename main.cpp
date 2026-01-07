#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include "enginev3/Engine.h"
#include "enginev3/init/SDLVideoLifecycleManager.h"
#include "platform/logging/ConsoleLogger.h"
#include "ui/window/SDLWindow.h"
#include "backend/sdl/input/SDLInputEventManager.h"
#include "core/units/Units.ixx"

using namespace Angina::Input;

class MyTestEngine : public Angina::EngineV3::Engine {
public:
	explicit MyTestEngine(
		Angina::Init::SubsystemLifecycleManagersPtr slms,
		Angina::Logging::LoggerPtr logger,
		Angina::UI::WindowPtr window,
		InputEventManagerPtr eventMgr
	):
		Angina::EngineV3::Engine(std::move(slms), std::move(logger), std::move(window), std::move(eventMgr), Angina::Units::RatePerSecond(60)) {}
protected:
	int beforeStart() override { return 0; }
	int beforeUpdate() override { return 0; }
	int afterUpdate() override { return 0; }
	int beforeEnd() override { return 0; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Angina::Logging::LoggerPtr log = std::make_unique<Angina::Logging::ConsoleLogger>();
	
	std::vector<std::shared_ptr<Angina::Init::ISubsystemLifecycleManager>> slmsVec;
	slmsVec.push_back(std::make_shared<Angina::Init::SDLVideoLifecycleManager>());
	auto slms = std::make_unique<Angina::Init::SubsystemLifecycleManagers>(slmsVec);
	Angina::UI::WindowConfig winConfig("Hi!", Angina::Units::AbsX(100), Angina::Units::AbsY(100), Angina::Units::Width(640), Angina::Units::Height(480));
	Angina::UI::WindowPtr window = Angina::UI::SDLWindow::make(winConfig);
	InputEventManagerPtr evMgr = SDLInputEventManager::make();
	
	MyTestEngine eng(std::move(slms), std::move(log), std::move(window), std::move(evMgr));
	eng.start();

	return EXIT_SUCCESS;
}
