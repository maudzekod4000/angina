#include "Engine.h"

#include "platform/time/WaitableTimer.h"
#include "platform/logging/ILogger.h"

using namespace Angina::EngineV3;
using namespace Angina::Init;
using namespace Angina::Logging;

Engine::Engine(const SubsystemLifecycleManagers& slms, Logger logger): subsystemLifecycleManagers(slms), logger(logger) {}

int Engine::start()
{
    if (const auto res = subsystemLifecycleManagers.init(0); res.error()) {
        logger->log(Level::ERROR, res.error());
        return -1; // Error codes enum would be useful but this far into the development its hard to say.
    }

    beforeStart();

    while (state.isRunning()) {
        beforeUpdate();
        afterUpdate();
    }

    beforeEnd();

    if (const auto res = subsystemLifecycleManagers.destroy(); res.error()) {
        logger->log(Level::ERROR, res.error());
        return -1; // Error codes enum would be useful but this far into the development its hard to say.
    }
    return 0;
}
