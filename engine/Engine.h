#ifndef V3_ENGINE_H
#define V3_ENGINE_H

#include "EngineState.h"

#include <filesystem>
#include <vector>
#include <string_view>

#include "core/error/Errors.h"
#include "core/identity/Id.h"

#include "platform/ui/window/IWindow.h"

#include "platform/init/SubsystemLifecycleManagers.h"
#include "platform/logging/ILogger.h"
#include "platform/input/IInputEventManager.h"
#include "platform/time/FramePacer.h"
#include "platform/resources/TextureResourceLoader.h"
#include "platform/resources/TextureTransferer.h"
#include "backend/sdl/rendering/SDLRenderer.h"

#include "core/datastructures/FreeList.h"
#include "backend/sdl/resources/SDLTexture.h"

#include "core/time/Stopwatch.h"
#include "core/units/Units.hpp"


namespace Angina::EngineV3 {

class Engine {
public:

	explicit Engine(
		Platform::Logging::LoggerPtr,
		Platform::UI::WindowPtr,
		Platform::Input::InputEventManagerPtr inputMgr,
		Core::Units::RatePerSecond desiredFPS,
		Backend::SDL::Rendering::SDLRenderer renderer,
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

	std::vector<Core::Identity::Id> textureIds; ///< Live textures.
	Platform::Logging::LoggerPtr logger;

	Backend::SDL::Resources::SDLTexture loadTexture(const char* filepath);
private:
	const Platform::Resources::TextureResourceLoaderPtr texResLoader;
	EngineState state;
	Platform::UI::WindowPtr window;

	Platform::Input::InputEventManagerPtr inputEventMgr;
	Backend::SDL::Rendering::SDLRenderer renderer;
	Platform::Resources::TextureTransfererPtr textureTransferer; ///< Used to transfer textures, from CPU to GPU, for example.

	Core::Units::RatePerSecond desiredFPS;
	Core::Time::Stopwatch globalClock; ///< Clock that runs from the start of the engine, monotonically, until the end and is never reset.
	Platform::Time::FramePacer framePacer; ///< Measures and stalls the main loop in order to provide a stable frame rate, i.e. each frame should take the same time.
	
	std::vector<Platform::System::Updateable*> systems;

	// TO DO: For textures we want a data structure that is:
	// We need a simple data structure that can hold the loaded textures
	// so we can manage their lifecycle.
	// I don;t even think we need to remove any textures, for the simplest
	// case of: 1. loading all textures at start
	// 2. deleting all textures at the end of the game
	// 3. all other things are optimizations.
	std::vector<Backend::SDL::Resources::SDLTexture> textures;

	// So for example, the game objects will have a SDLTexture field
	// when we are quitting the game we first delete the game objects
	// as they are more superficial and then we delete the textures
	// it is more explicit control of the lifecycle, but at least its
	// plain to see what the behavior is. It's more C-like style.
};

}

#endif

