#ifndef V3_ENGINE_H
#define V3_ENGINE_H

#include "EngineState.h"

#include <filesystem>
#include <vector>

#include "core/error/Errors.h"
#include "core/identity/Id.h"

#include "platform/ui/window/IWindow.h"

#include "platform/init/SubsystemLifecycleManagers.h"
#include "platform/logging/ILogger.h"
#include "platform/input/IInputEventManager.h"
#include "platform/time/FramePacer.h"
#include "platform/resources/TextureResourceLoader.h"
#include "platform/rendering/Renderer.h"
#include "platform/resources/TextureTransferer.h"

#include "core/time/Stopwatch.h"
#include "core/units/Units.hpp"


namespace Angina::EngineV3 {

class Engine {
public:

	explicit Engine(
		Platform::Init::SubsystemLifecycleManagersPtr,
		Platform::Logging::LoggerPtr,
		Platform::UI::WindowPtr,
		Platform::Input::InputEventManagerPtr inputMgr,
		Core::Units::RatePerSecond desiredFPS,
		Platform::Rendering::RendererPtr renderer,
		Platform::Resources::TextureResourceLoaderPtr texLoader
	);

	virtual ~Engine() = default;

	/// Initializes subsystems and, if successful, starts the main loop.
	Core::Errors::ErrorCode start();
protected:
	/// Run after the subsystems are initialized, but before the main loop has started.
	virtual Core::Errors::ErrorCode beforeStart() = 0;

	/// Run before update of the subsystems, i.e. physics, animation.
	virtual Core::Errors::ErrorCode beforeUpdate() = 0;

	/// Run after update of the subsystems, i.e. physics, animation.
	virtual Core::Errors::ErrorCode afterUpdate() = 0;

	/// Run after the main loop has exited.
	virtual Core::Errors::ErrorCode beforeEnd() = 0;

	std::vector<Core::Identity::Id> textureIds;
	Platform::Logging::LoggerPtr logger;

	std::vector<Platform::Resources::IdOrError> load(const std::vector<std::filesystem::path>&);
private:
	const Platform::Resources::TextureResourceLoaderPtr texResLoader;
	EngineState state;
	Platform::Init::SubsystemLifecycleManagersPtr subsystemLifecycleManagers;
	Platform::UI::WindowPtr window;

	Platform::Input::InputEventManagerPtr inputEventMgr;
	Platform::Rendering::RendererPtr renderer;
	Platform::Resources::TextureTransfererPtr textureTransferer; ///< Used to transfer textures, from CPU to GPU, for example.

	Core::Units::RatePerSecond desiredFPS;
	Core::Time::Stopwatch globalClock; ///< Clock that runs from the start of the engine, monotonically, until the end and is never reset.
	Platform::Time::FramePacer framePacer; ///< Measures and stalls the main loop in order to provide a stable frame rate, i.e. each frame should take the same time.
	
	std::vector<Platform::System::Updateable*> systems;
};

}

#endif

