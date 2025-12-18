#include "Engine.h"

#include "platform/time/WaitableTimer.h"
#include "platform/logging/ILogger.h"

using namespace Angina::EngineV3;
using namespace Angina::Init;
using namespace Angina::Logging;
using namespace Angina::UI;

Engine::Engine(SubsystemLifecycleManagers slms, LoggerPtr logger, WindowPtr window):
    subsystemLifecycleManagers(std::move(slms)),
    logger(logger),
    window(window)
{}

int Engine::start()
{
    if (const auto res = subsystemLifecycleManagers.init(0); res.has_value() == false) {
        logger->log(Level::ERROR, res.error());
        return -1; // Error codes enum would be useful but this far into the development its hard to say.
    }

    beforeStart();

    // TOTHINK: Maybe it is good to pass this state from the outside so we can control it?
    state.set(EngineState::State::RUNNING);

    while (state.isRunning()) {
        beforeUpdate();
        afterUpdate();
    }

    beforeEnd();

    if (const auto res = subsystemLifecycleManagers.destroy(); res.has_value() == false) {
        logger->log(Level::ERROR, res.error());
        return -1; // Error codes enum would be useful but this far into the development its hard to say.
    }
    return 0;
}
