#include "Engine.h"

#include <cassert>
#include <optional>

using namespace Angina::EngineV3;
using namespace Platform::Init;
using namespace Platform::Logging;
using namespace Platform::UI;
using namespace Platform::Input;
using namespace Platform::System;
using namespace Platform::Resources;
using namespace Platform::Rendering;
using namespace Core::Units;
using namespace Core::Errors;

Engine::Engine(
    SubsystemLifecycleManagersPtr slms,
    LoggerPtr logger,
    WindowPtr window,
    InputEventManagerPtr inputMgr,
    RatePerSecond desiredFPS,
    RendererPtr renderer,
    TextureResourceLoaderPtr texLoader
):
    subsystemLifecycleManagers(std::move(slms)),
    logger(std::move(logger)),
    window(std::move(window)),
    inputEventMgr(std::move(inputMgr)),
    renderer(std::move(renderer)),
    texResLoader(std::move(texLoader)),
    desiredFPS(desiredFPS),
    globalClock({}),
    framePacer(desiredFPS, globalClock)
{
    assert(this->subsystemLifecycleManagers);
    assert(this->logger);
    assert(this->window);
    assert(this->inputEventMgr);
    assert(this->texResLoader);

    systems.push_back(this->inputEventMgr.get());
}

std::vector<IdOrError> Engine::load(const std::vector<std::filesystem::path>& paths) {
    const auto idsOrErrors = texResLoader->load(paths);
    texResLoader->wait();
    return idsOrErrors;
}

ErrorCode Engine::start()
{
    if (const auto err = subsystemLifecycleManagers->init(0); err) {
        return err;
    }

    // Lambda so we can early-return on hook errors while always reaching destroy().
    // ErrorCode has const members and is not assignable, only copy-constructible.
    auto runMain = [&]() -> std::optional<ErrorCode> {
        if (const auto err = beforeStart(); err) {
            return err;
        }

        // TOTHINK: Maybe it is good to pass this state from the outside so we can control it?
        state.set(EngineState::State::RUNNING);
        globalClock.reset(); // One and only call to 'reset'

        while (state.isRunning()) {
            framePacer.startFrame();

            if (const auto err = beforeUpdate(); err) {
                return err;
            }

            for (int i = 0; i < int(Phase::Count); i++) {
                for (auto system : systems) {
                    system->update(static_cast<Phase>(i));
                }
            }

            renderer->clear();
            for (const auto id : textureIds) {
                renderer->render(texResLoader->resolve(id));
            }
            renderer->present();

            if (const auto err = afterUpdate(); err) {
                return err;
            }

            // This code might be in a callback if we use the observable pattern.
            if (inputEventMgr->getSnapshot().quit) {
                state.set(EngineState::State::STOPPING);
            }

            // TODO: It would be nice to have some statistics on
            // How much of the frame time was work vs. waiting.
            // This might show us how much headroom we got.
            framePacer.endFrame();
        }

        if (const auto err = beforeEnd(); err) {
            return err;
        }

        return std::nullopt;
    };

    const auto mainErr = runMain();

    if (const auto err = subsystemLifecycleManagers->destroy(); err) {
        if (!mainErr) return err;
    }

    if (mainErr) return *mainErr;
    return {};
}
