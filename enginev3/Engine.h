#ifndef V3_ENGINE_H
#define V3_ENGINE_H

#include "enginev3/EngineState.h"
#include "enginev3/init/SubsystemLifecycleManagers.h"
#include "ui/window/BaseWindow.h"
#include "platform/logging/ILogger.h"
#include "platform/input/IInputEventManager.h"
#include "core/units/Units.ixx"

namespace Angina::EngineV3 {

class Engine {
public:

	// Note: Hm....It might be better to have the logger, window and input manager as unique pointers and 
	// create them outside but transfer ownership to the engine...
	// The other option is to have a wrapper around the engine which will configure the engine-related stuff.
	// It will take care of the ownership and will pass just references to the engine.
	// something like a DI container.
	// Ok, I suppose i will create the dependencies outside and transfer ownership to the Engine class via move.
	// OKKKKK so make sure that you create the dependencies outside and then pass them to the ENGINE KHUAK KHUAAAK
	explicit Engine(
		Init::SubsystemLifecycleManagersPtr,
		Logging::LoggerPtr,
		UI::WindowPtr,
		Input::InputEventManagerPtr inputMgr,
		Units::RatePerSecond desiredFPS // Haha I added 'desired' before the FPS ;) wink wink, all bets are off!
	);

	virtual ~Engine() = default;

	/// Initializes subsystems and, if successful, starts the main loop.
	/// @return Non-zero if there was an error.
	int start();
protected:
	/// Run after the subsystems are initialized, but before the main loop has started.
	/// @return Non-zero if there was an error.
	virtual int beforeStart() = 0;

	/// Run before update of the subsystems, i.e. physics, animation.
	/// @return Non-zero if there was an error.
	virtual int beforeUpdate() = 0;

	/// Run after update of the subsystems, i.e. physics, animation.
	/// @return Non-zero if there was an error.
	virtual int afterUpdate() = 0;

	/// Run after the main loop has exited.
	/// @return Non-zero if there was an error.
	virtual int beforeEnd() = 0;
private:
	EngineState state;
	Init::SubsystemLifecycleManagersPtr subsystemLifecycleManagers;
	Logging::LoggerPtr logger;
	UI::WindowPtr window;
	Input::InputEventManagerPtr inputEventMgr;
	Units::RatePerSecond desiredFPS;

	/// Returns true when a quit event has been detected.
	bool processInput();
};

}

#endif

