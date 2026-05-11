#include "SDLEngine.h"

#include <memory>

#include "platform/init/SubsystemLifecycleManagers.h"
#include "backend/sdl/init/SDLVideoLifecycleManager.h"
#include "platform/logging/ConsoleLogger.h"
#include "backend/sdl/ui/SDLWindow.h"
#include "backend/sdl/input/SDLInputEventManager.h"

using namespace EngineImpl::SDL;
using namespace Platform::Init;
using namespace Core::Units;
using namespace Backend::SDL::Init;
using namespace Backend::SDL::Input;
using namespace Backend::SDL::UI;
using namespace Platform::Logging;
using namespace Platform::UI;
using namespace Angina::EngineV3;

SDLEngine::SDLEngine(const WindowConfig& wc, RatePerSecond desiredFPS):
	Engine(
		std::vector<std::shared_ptr<ISubsystemLifecycleManager>> {
			std::make_shared<SDLVideoLifecycleManager>()
		},
		std::make_unique<ConsoleLogger>(),
		SDLWindow::make(wc),
		SDLInputEventManager::make(),
		desiredFPS,
		Engine::window->makeRenderer()
	) {
}