#ifndef V3_ENGINE_H
#define V3_ENGINE_H

#include "EngineState.h"

#include <filesystem>
#include <vector>
#include <string_view>

#include "core/error/Errors.h"
#include "core/identity/Id.h"

#include "platform/init/SubsystemLifecycleManagers.h"
#include "platform/logging/ILogger.h"
#include "platform/input/IInputEventManager.h"
#include "platform/time/FramePacer.h"
#include "platform/resources/TextureResourceLoader.h"
#include "platform/resources/TextureTransferer.h"
#include "backend/sdl/rendering/SDLRenderer.h"

#include "core/datastructures/FreeList.h"
#include "backend/sdl/resources/SDLTexture.h"
#include "backend/sdl/input/SDLInputEventManager.h"

#include "core/time/Stopwatch.h"
#include "core/units/Units.hpp"

#include "platform/logging/ConsoleLogger.h"
#include "backend/sdl/ui/SDLWindow.h"
#include "platform/ui/window/WindowConfig.h"

namespace Angina::EngineV3 {

class Engine {
	explicit Engine(
		Core::Units::RatePerSecond desiredFPS,
		Backend::SDL::Rendering::SDLRenderer renderer,
		Backend::SDL::UI::SDLWindow window
	);
public:
	static Engine make(const Platform::UI::WindowConfig& winCfg, Core::Units::RatePerSecond fps, Core::Errors::ErrorCode&);

	/// Initializes subsystems and, if successful, starts the main loop.
	Core::Errors::ErrorCode start();

	Backend::SDL::Resources::SDLTexture loadTexture(const char* filepath);
private:
	Backend::SDL::Rendering::SDLRenderer renderer;
	Backend::SDL::UI::SDLWindow window;
	Backend::SDL::Input::SDLInputEventManager inputEventMgr;
	std::vector<Backend::SDL::Resources::SDLTexture> textures;
	
	EngineState state;
	Core::Units::RatePerSecond desiredFPS;
	Core::Time::Stopwatch globalClock; ///< Clock that runs from the start of the engine, monotonically, until the end and is never reset.
	Platform::Time::FramePacer framePacer; ///< Measures and stalls the main loop in order to provide a stable frame rate, i.e. each frame should take the same time.
	
	Platform::Logging::ConsoleLogger logger;

	// TO DO: For textures we want a data structure that is:
	// We need a simple data structure that can hold the loaded textures
	// so we can manage their lifecycle.
	// I don;t even think we need to remove any textures, for the simplest
	// case of: 1. loading all textures at start
	// 2. deleting all textures at the end of the game
	// 3. all other things are optimizations.

	// So for example, the game objects will have a SDLTexture field
	// when we are quitting the game we first delete the game objects
	// as they are more superficial and then we delete the textures
	// it is more explicit control of the lifecycle, but at least its
	// plain to see what the behavior is. It's more C-like style.
};

}

#endif

