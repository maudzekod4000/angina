#include "SDLEngine.h"

#include <cstdlib>
#include <memory>
#include <vector>

#include "platform/init/SubsystemLifecycleManagers.h"
#include "platform/logging/ConsoleLogger.h"
#include "platform/resources/GPUTextureLoader.h"
#include "backend/sdl/init/SDLVideoLifecycleManager.h"
#include "backend/sdl/ui/SDLWindow.h"
#include "backend/sdl/input/SDLInputEventManager.h"
#include "backend/sdl/resources/SDLCPUTextureResourceLoader.h"
#include "backend/sdl/rendering/SDLRenderer.h"

using namespace EngineImpl::SDL;
using namespace Platform::UI;
using namespace Platform::Logging;

SDLEngine::Resources SDLEngine::build(const WindowConfig& config) {
	auto slms = std::make_unique<Platform::Init::SubsystemLifecycleManagers>(
		std::vector<std::shared_ptr<Platform::Init::ISubsystemLifecycleManager>>{
			std::make_shared<Backend::SDL::Init::SDLVideoLifecycleManager>()
		}
	);
	auto logger = std::make_unique<Platform::Logging::ConsoleLogger>();

	auto windowOrErr = Backend::SDL::UI::SDLWindow::make(config);
	if (!windowOrErr) {
		logger->log(Level::ERROR, windowOrErr.error());
		std::exit(EXIT_FAILURE);
	}
	auto window = std::move(windowOrErr.value());

	auto rendererOrErr = window->makeRenderer();
	if (!rendererOrErr) {
		logger->log(Level::ERROR, rendererOrErr.error());
		std::exit(EXIT_FAILURE);
	}

	auto inputMgr = Backend::SDL::Input::SDLInputEventManager::make();
	auto sdlRenderer = Backend::SDL::Rendering::SDLRenderer::makeShared(rendererOrErr.value());
	auto cpuTexLoader = Backend::SDL::Resources::SDLCPUTextureResourceLoader::make();
	auto texLoader = std::make_unique<Platform::Resources::GPUTextureLoader>(sdlRenderer, std::move(cpuTexLoader));

	return {
		std::move(slms),
		std::move(logger),
		std::move(window),
		std::move(inputMgr),
		std::move(sdlRenderer),
		std::move(texLoader)
	};
}

SDLEngine::SDLEngine(const WindowConfig& config, Core::Units::RatePerSecond fps)
	: SDLEngine(build(config), fps) {}

SDLEngine::SDLEngine(Resources res, Core::Units::RatePerSecond fps)
	: Angina::EngineV3::Engine(
		std::move(res.slms),
		std::move(res.logger),
		std::move(res.window),
		std::move(res.inputMgr),
		fps,
		std::move(res.renderer),
		std::move(res.texLoader)
	) {}
