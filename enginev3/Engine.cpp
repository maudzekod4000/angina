#include "Engine.h"

#include "platform/time/WaitableTimer.h"

using namespace Angina::EngineV3;
using namespace Angina::Init;

Engine::Engine(const SubsystemLifecycleManagers& slms): subsystemLifecycleManagers(slms) {}

int Engine::start()
{
    subsystemLifecycleManagers.init(0);
    beforeStart();

    while (state.isRunning()) {
        beforeUpdate();
        afterUpdate();
    }

    beforeEnd();
    subsystemLifecycleManagers.destroy();
    return 0;
}
