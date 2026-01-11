#ifndef V3_ENGINE_H
#define V3_ENGINE_H

#include "EngineState.h"

#include "ui/window/IWindow.h"

#include "platform/init/SubsystemLifecycleManagers.h"
#include "platform/logging/ILogger.h"
#include "platform/input/IInputEventManager.h"
#include "platform/time/FramePacer.h"

#include "core/time/Stopwatch.h"
#include "core/units/Units.hpp"

namespace Angina::EngineV3 {

class Engine {
public:

	explicit Engine(
		Init::SubsystemLifecycleManagersPtr,
		Logging::LoggerPtr,
		UI::WindowPtr,
		Input::InputEventManagerPtr inputMgr,
		Core::Units::RatePerSecond desiredFPS
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
	Core::Units::RatePerSecond desiredFPS;
	Core::Time::Stopwatch globalClock; ///< Clock that runs from the start of the engine, monotonically, until the end and is never reset.
	Platform::Time::FramePacer framePacer; ///< Measures and stalls the main loop in order to provide a stable frame rate, i.e. each frame should take the same time.

	/// Returns true when a quit event has been detected.
	bool processInput();
};

}

#endif

