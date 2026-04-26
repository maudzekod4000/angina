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
#include "backend/sdl/resources/SDLCPUTextureResourceLoader.h"
#include "core/units/Units.hpp"
#include "platform/resources/GPUTextureLoader.h"
#include "backend/sdl/rendering/SDLRenderer.h"

class MyTestEngine : public Angina::EngineV3::Engine {
public:
	explicit MyTestEngine(
		Platform::Init::SubsystemLifecycleManagersPtr slms,
		Platform::Logging::LoggerPtr logger,
		Platform::UI::WindowPtr window,
		Platform::Input::InputEventManagerPtr eventMgr,
		Platform::Resources::GPUTextureResourceLoaderPtr gpuTexLoader,
		Platform::Rendering::RendererPtr renderer
	):
		Angina::EngineV3::Engine(std::move(slms), std::move(logger), std::move(window), std::move(eventMgr), Core::Units::RatePerSecond(60), std::move(gpuTexLoader), std::move(renderer)) {}
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
	auto window = Backend::SDL::UI::SDLWindow::make(winConfig);
	Platform::Input::InputEventManagerPtr evMgr = Backend::SDL::Input::SDLInputEventManager::make();
	auto texResLoader = Backend::SDL::Resources::SDLCPUTextureResourceLoader::make();
	auto rendererOrErr = window->makeRenderer();

	// It would be good to create a factory for the SDL implementation.
	// Thats a bit annoying...
	// So sometimes i need one instance of a object for one purpose and another for another purpose.
	// I want to create them from the outside and 
	// Ahhhhh sooo that's why we have shared pointers hahaha
	// With shared pointers, I can create one instance of the Renderer and share it between
	// The engine (for rendering) and the GPUTextureLoader for transferring textures to the GPU.

	if (!rendererOrErr.has_value()) {
		// Print the error....
		return EXIT_FAILURE;
	}

	auto renderer = Backend::SDL::Rendering::SDLRenderer::makeShared(rendererOrErr.value()); // The window has to give birth to the renderer.

	auto gpuTexLoader = std::make_unique<Platform::Resources::GPUTextureLoader>(renderer, std::move(texResLoader));
	
	MyTestEngine eng(std::move(slms), std::move(log), std::move(window), std::move(evMgr), std::move(gpuTexLoader), renderer);
	eng.start();

	return EXIT_SUCCESS;
}
