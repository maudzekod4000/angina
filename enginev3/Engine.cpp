#include "Engine.h"

#include <cassert>

#include "platform/time/WaitableTimer.h"
#include "platform/logging/ILogger.h"

using namespace Angina::EngineV3;
using namespace Angina::Init;
using namespace Angina::Logging;
using namespace Angina::UI;
using namespace Angina::Input;

Engine::Engine(
    SubsystemLifecycleManagers slms,
    LoggerPtr logger,
    WindowPtr window,
    InputEventManagerPtr inputMgr
):
    subsystemLifecycleManagers(std::move(slms)),
    logger(logger),
    window(window),
    inputEventMgr(std::move(inputMgr))
{
    assert(logger);
    assert(window);
    assert(inputEventMgr);
}

int Engine::start()
{
    if (const auto res = subsystemLifecycleManagers.init(0); res.has_value() == false) {
        logger->log(Level::ERROR, res.error());
        return -1; // Error codes enum would be useful but this far into the development its hard to say.
    }

    beforeStart();

    // TOTHINK: Maybe it is good to pass this state from the outside so we can control it?
    state.set(EngineState::State::RUNNING);
    
    if (const auto res = inputEventMgr->start(); res.has_value() == false) {
        logger->log(Level::ERROR, res.error());
        return -1;
    }

    while (state.isRunning()) {
        if (const bool quit = processInput(); quit) {
            break;
        }

        beforeUpdate();
        afterUpdate();
    }

    beforeEnd();

    // TODO: I think the start method of the engine should return either expected or just a ErrorCode
    // And then the caller should log on critical stuff. 
    // The engine will also log but just as to say what is going on.
    if (const auto res = inputEventMgr->stop(); res.has_value() == false) {
        logger->log(Level::ERROR, res.error());
        return -1;
    }

    if (const auto res = subsystemLifecycleManagers.destroy(); res.has_value() == false) {
        logger->log(Level::ERROR, res.error());
        return -1; // Error codes enum would be useful but this far into the development its hard to say.
    }
    return 0;
}

bool Engine::processInput()
{
    const InputSnapshot input = inputEventMgr->getSnapshot();

    if (input.quit) {
        return true;
    }

    return false;
}
