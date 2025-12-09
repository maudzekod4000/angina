#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "enginev3/Engine.h"

class MyTestEngine : public Angina::EngineV3::Engine {
public:
	explicit MyTestEngine(const Angina::Init::SubsystemLifecycleManagers& slms): Angina::EngineV3::Engine(slms) {}
protected:
	int beforeStart() override { return 0; }
	int beforeUpdate() override { return 0; }
	int afterUpdate() override { return 0; }
	int beforeEnd() override { return 0; }
};

#undef main

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char **argv) {
	std::vector<Angina::Init::ISubsystemLifecycleManager> slmsVec;
	Angina::Init::SubsystemLifecycleManagers slms(slmsVec);
	MyTestEngine eng(slms);
	eng.start();

	return EXIT_SUCCESS;
}
