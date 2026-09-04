#include "Engine.h"

#include <cassert>

#include "backend/sdl/resources/SDLTexLoader.h"
#include "backend/sdl/init/SDLVideoLifecycleManager.h"

using namespace Angina::EngineV3;
using namespace Platform::Init;
using namespace Platform::Logging;
using namespace Platform::UI;
using namespace Platform::Input;
using namespace Platform::System;
using namespace Platform::Resources;
using namespace Core::Units;
using namespace Core::Errors;
using namespace Backend::SDL;

Engine::Engine(
    LoggerPtr logger,
    WindowPtr window,
    InputEventManagerPtr inputMgr,
    RatePerSecond desiredFPS,
    Backend::SDL::Rendering::SDLRenderer renderer,
    TextureResourceLoaderPtr texLoader
):
    logger(std::move(logger)),
    window(std::move(window)),
    inputEventMgr(std::move(inputMgr)),
    renderer(renderer),
    texResLoader(std::move(texLoader)),
    desiredFPS(desiredFPS),
    globalClock({}),
    framePacer(desiredFPS, globalClock)
{
    assert(this->logger);
    assert(this->window);
    assert(this->inputEventMgr);
    assert(this->texResLoader);

    systems.push_back(this->inputEventMgr.get());
}

Backend::SDL::Resources::SDLTexture Engine::loadTexture(const char* filepath) {
    using namespace Backend::SDL::Resources;
    
    ErrorCode err;
    SDLTexture tex = load(filepath, renderer.handle, err);

    if (err) {
        logger->log(Level::ERROR, err);
        return SDLTexture(); // TODO: Return a proper error, so that the client knows it failed
        // or better -> load a default texture for maximum UX or Dev Ex
        // This default texture will be loaded when the engine starts and cached in the 
        // Engine as a field.
    }

    textures.push_back(tex);
    return tex;
}

ErrorCode Engine::start()
{
    if (const auto err = Init::initVideo(0); err) {
        return err;
    }

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

        renderer.clear();
        for (const auto& tex : textures) {
            renderer.render(tex);
        }
        renderer.present();

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

    if (const auto err = subsystemLifecycleManagers->destroy(); err) {
        return err;
    }

    return {};
}
