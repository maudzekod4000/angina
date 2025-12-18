#ifndef V3_ENGINE_H
#define V3_ENGINE_H

#include "enginev3/EngineState.h"
#include "enginev3/init/SubsystemLifecycleManagers.h"
#include "ui/window/BaseWindow.h"
#include "platform/logging/ILogger.h"

namespace Angina::EngineV3 {

class Engine {
public:
	explicit Engine(
		Init::SubsystemLifecycleManagers,
		Logging::LoggerPtr,
		UI::WindowPtr
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
	Init::SubsystemLifecycleManagers subsystemLifecycleManagers;
	Logging::LoggerPtr logger;
	UI::WindowPtr window;
};

}

#endif

