#include "Engine.h"

#include <cassert>

#include "backend/sdl/resources/SDLTexLoader.h"
#include "backend/sdl/init/SDLVideoLifecycleManager.h"

using namespace Angina::EngineV3;
using namespace Platform::Init;
using namespace Platform::Logging;
using namespace Platform::Input;
using namespace Platform::System;
using namespace Platform::Resources;
using namespace Core::Units;
using namespace Core::Errors;
using namespace Backend::SDL;

Engine::Engine(
    RatePerSecond desiredFPS,
    Backend::SDL::Rendering::SDLRenderer renderer,
    Backend::SDL::UI::SDLWindow window
):
    renderer(renderer),
    window(window),
    desiredFPS(desiredFPS),
    globalClock({}),
    framePacer(desiredFPS, globalClock)
{
}

Engine Angina::EngineV3::Engine::make(const Platform::UI::WindowConfig& winCfg, Core::Units::RatePerSecond fps, Core::Errors::ErrorCode& err)
{
    UI::SDLWindow window = UI::SDLWindow::make(winCfg, err);

    if (err) {
        return Engine(fps, Rendering::SDLRenderer(), window);
    }

    SDL_Renderer* sdlRenderer = window.makeRenderer(err);

    if (err) {
        return Engine(fps, Rendering::SDLRenderer(sdlRenderer), window);
    }

    Rendering::SDLRenderer renderer(sdlRenderer);

    return Engine(fps, renderer, window);
}

Backend::SDL::Resources::SDLTexture Engine::loadTexture(const char* filepath) {
    using namespace Backend::SDL::Resources;
    
    ErrorCode err;
    SDLTexture tex = load(filepath, renderer.handle, err);

    if (err) {
        logger.log(Level::ERROR, err);
        return SDLTexture(); // TODO: Return a proper error, so that the client knows it failed
        // or better -> load a default texture for maximum UX or Dev Ex
        // This default texture will be loaded when the engine starts and cached in the 
        // Engine as a field.
    }

    textures.push_back(tex);
    return tex;
}

void Angina::EngineV3::Engine::beforeGameLoop()
{
    Resources::SDLTexture ballsTex = loadTexture("resources/engine/balls.png");
    // Sometimes we will use the original texture's w/h but sometimes we need to overwrite it.
    // TODO: Hmmm...soo the creation of the object needs to be thought out
    // but lets just do manual creation and then we will see the patterns in the 
    // creation and we will adjust.
    GameObject redBall{ballsTex, 0, 0, 100, 100};
    gameObjects.push_back(redBall);
    SpriteAnim redBallFrame{ {Core::Units::Rect{0, 0, 100, 100}}, 0.0f };
    gameObjSpriteAnim.push_back(redBallFrame);

    GameObject greenBall{ ballsTex, 540, 0, 100, 100 };
    gameObjects.push_back(greenBall);
    SpriteAnim greenBallFrame{ {Core::Units::Rect{100, 0, 100, 100}}, 0.0f };
    gameObjSpriteAnim.push_back(greenBallFrame);

    GameObject yellowBall{ ballsTex, 0, 380, 100, 100 };
    gameObjects.push_back(yellowBall);
    SpriteAnim yellowBallFrame{ {Core::Units::Rect{0, 100, 100, 100}} };
    gameObjSpriteAnim.push_back(yellowBallFrame);

    GameObject blueBall{ ballsTex, 540, 380, 100, 100 };
    gameObjects.push_back(blueBall);
    SpriteAnim blueBallFrame{ {Core::Units::Rect{100, 100, 100, 100}} };
    gameObjSpriteAnim.push_back(blueBallFrame);

    // TODO: Sooo i think that the whole sprite thing has to go in a separate structure
    // that will be somewhat of a animation controller
    // we will just need to keep a 1-to-1 correspondence between the object index and the
    // animation index.
    // If a object does not have an animation it will hold a 1 sprite frame.
}

ErrorCode Engine::start()
{
    if (const auto err = Init::initVideo(0); err) {
        return err;
    }

    beforeGameLoop();

    state.set(EngineState::State::RUNNING);
    globalClock.reset(); // One and only call to 'reset'

    while (state.isRunning()) {
        framePacer.startFrame();

        for (int i = 0; i < int(Phase::Count); i++) {
            // update systems
            inputEventMgr.update(Phase(i));
        }

        renderer.clear();
        for (int i = 0; i < gameObjects.size(); i++) {
            const GameObject& gameObject = gameObjects[i];
            const SpriteAnim& spriteAnim = gameObjSpriteAnim[i];
            renderer.render(gameObject.texture, gameObject.x, gameObject.y,
                gameObject.w, gameObject.h, spriteAnim);

        }
        renderer.present();

        if (inputEventMgr.inEvent.quit) {
            state.set(EngineState::State::STOPPING);
        }

        // TODO: It would be nice to have some statistics on
        // How much of the frame time was work vs. waiting.
        // This might show us how much headroom we got.
        framePacer.endFrame();
    }

    Init::destroyVideo();

    return {};
}
