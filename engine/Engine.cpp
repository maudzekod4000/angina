#include "Engine.h"

#include <cassert>

#include "platform/logging/ILogger.h"

using namespace Angina::EngineV3;
using namespace Platform::Init;
using namespace Platform::Logging;
using namespace Platform::UI;
using namespace Platform::Input;
using namespace Core::Units;

Engine::Engine(
    SubsystemLifecycleManagersPtr slms,
    LoggerPtr logger,
    WindowPtr window,
    InputEventManagerPtr inputMgr,
    RatePerSecond desiredFPS
):
    subsystemLifecycleManagers(std::move(slms)),
    logger(std::move(logger)),
    window(std::move(window)),
    inputEventMgr(std::move(inputMgr)),
    desiredFPS(desiredFPS),
    globalClock({}),
    framePacer(desiredFPS, globalClock)
{
    assert(this->subsystemLifecycleManagers);
    assert(this->logger);
    assert(this->window);
    assert(this->inputEventMgr);

    systems.push_back(this->inputEventMgr.get());
}

int Engine::start()
{
    if (const auto err = subsystemLifecycleManagers->init(0); err) {
        logger->log(Level::ERROR, err);
        return -1; // Error codes enum would be useful but this far into the development its hard to say.
    }

    beforeStart();

    // TOTHINK: Maybe it is good to pass this state from the outside so we can control it?
    state.set(EngineState::State::RUNNING);
    globalClock.reset(); // One and only call to 'reset'

    while (state.isRunning()) {
        framePacer.startFrame();

        beforeUpdate();

        // update the physics, etc.
        for (auto system : systems) {
            system->update(); // TODO: add the Phase parameter to the updateable interface...and maybe the name of the interface should be PhaseUpdateable
        }
        // TODO: There might be benefit in using a callback for the user events.
        // Then we can offload code from here and order the listeners
        // But lets see how it looks here first.

        afterUpdate();

        // This code might be in a callback if we use the observable pattern.
        if (inputEventMgr->getSnapshot().quit) {
            state.set(EngineState::State::STOPPING);
        }
        framePacer.endFrame();
    }

    beforeEnd();

    // TODO: I think the start method of the engine should return either expected or just a ErrorCode
    // And then the caller should log on critical stuff. 
    // The engine will also log but just as to say what is going on.

    if (const auto err = subsystemLifecycleManagers->destroy(); err) {
        logger->log(Level::ERROR, err);
        return -1;
    }
    return 0;
}

bool Engine::processInput()
{
    // Poll events
    if (const auto err = inputEventMgr->update(); err) {
        return false;
    }

    // Read and process the input.
    // Now.........this might not happen like that later, I want to have a multithreaded engine, but the frickin` SDL is so goddamn BAD....
    // I should not be too harsh tho because miss OPERATING SYSTEM has too much capriche...................................................
    const InputSnapshot input = inputEventMgr->getSnapshot();

    if (input.quit) {
        return true;
    }

    return false;
}
