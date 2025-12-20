#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include "enginev3/Engine.h"
#include "enginev3/init/SDLVideoLifecycleManager.h"
#include "platform/logging/ConsoleLogger.h"
#include "ui/window/SDLWindow.h"

class MyTestEngine : public Angina::EngineV3::Engine {
public:
	explicit MyTestEngine(Angina::Init::SubsystemLifecycleManagers slms, Angina::Logging::LoggerPtr logger, Angina::UI::WindowPtr window):
		Angina::EngineV3::Engine(std::move(slms), logger, window) {}
protected:
	int beforeStart() override { return 0; }
	int beforeUpdate() override { return 0; }
	int afterUpdate() override { return 0; }
	int beforeEnd() override { return 0; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Angina::Logging::LoggerPtr log = std::make_shared<Angina::Logging::ConsoleLogger>();
	
	std::vector<std::shared_ptr<Angina::Init::ISubsystemLifecycleManager>> slmsVec;
	slmsVec.push_back(std::make_shared<Angina::Init::SDLVideoLifecycleManager>());
	Angina::Init::SubsystemLifecycleManagers slms(slmsVec);
	Angina::UI::WindowConfig winConfig("Hi!", Angina::Units::AbsX(0), Angina::Units::AbsY(0),
		Angina::Units::Width(640), Angina::Units::Height(480));
	Angina::UI::WindowPtr window = Angina::UI::SDLWindow::make(winConfig);
	
	MyTestEngine eng(std::move(slms), log, window);
	eng.start();

	return EXIT_SUCCESS;
}
