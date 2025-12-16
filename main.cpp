#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "enginev3/Engine.h"
#include "enginev3/init/SDLVideoLifecycleManager.h"
#include "platform/logging/Logger.h"
#include "platform/logging/ConsoleLogger.h"

class MyTestEngine : public Angina::EngineV3::Engine {
public:
	explicit MyTestEngine(const Angina::Init::SubsystemLifecycleManagers& slms, Angina::Logging::Logger logger): Angina::EngineV3::Engine(slms, logger) {}
protected:
	int beforeStart() override { return 0; }
	int beforeUpdate() override { return 0; }
	int afterUpdate() override { return 0; }
	int beforeEnd() override { return 0; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	Angina::Logging::Logger log(std::make_shared<Angina::Logging::ConsoleLogger>());
	
	std::vector<std::shared_ptr<Angina::Init::ISubsystemLifecycleManager>> slmsVec;
	slmsVec.push_back(std::make_shared<Angina::Init::SDLVideoLifecycleManager>());
	Angina::Init::SubsystemLifecycleManagers slms(slmsVec);
	
	MyTestEngine eng(slms, log);
	eng.start();

	return EXIT_SUCCESS;
}
