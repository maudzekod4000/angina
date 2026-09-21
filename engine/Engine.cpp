#include "Engine.h"

#include <cmath>

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
    Resources::SDLTexture stickfigureTex = loadTexture("resources/engine/stickfigure.png");
    // Sometimes we will use the original texture's w/h but sometimes we need to overwrite it.
    // TODO: Hmmm...soo the creation of the object needs to be thought out
    // but lets just do manual creation and then we will see the patterns in the 
    // creation and we will adjust.
    GameObject stickfigure{stickfigureTex, 64, 205};
    gameObjects.push_back(stickfigure);

    Animation stickAnim(4);
    animations.push_back(stickAnim);

    Movement stickMov;
    //stickMov.start(300, 200, 150);
    movements.push_back(stickMov);
    inputEventMgr.onClickHandler = [this](int x, int y) {
        movements[0].start(x, y, 150);
    };
    movements[0].onMovementStart = [this]() {
        animations[0].start(1000);
    };
    movements[0].onMovementEnd = [this]() {
        animations[0].stop();
    };

    /*Resources::SDLTexture ballsTex = loadTexture("resources/engine/balls.png");
    GameObject balls{ ballsTex, 200, 200 };
    gameObjects.push_back(balls);

    Animation ballsAnim(1);
    animations.push_back(ballsAnim);

    Movement ballsMov;
    movements.push_back(ballsMov);*/

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
        
        /* State Updates */
        inputEventMgr.update();

        for (Animation& anim : animations) {
            anim.update();
        }

        for (Movement& mov : movements) {
            mov.update();
        }
        /* End State Updates */

        /* React to input */

        /* End react to input */

        /* Rendering */
        renderer.clear();

        // So idk, maybe this rendering part can be just over the Animation thingies...
        // but lets see...
        for (int i = 0; i < gameObjects.size(); i++) {
            const GameObject& gameObject = gameObjects[i];
            const Animation& spriteAnim = animations[i];
            const Movement& movement = movements[i];
            int texOffX = gameObject.w * spriteAnim.currentFrameIdx;

            renderer.render(gameObject.texture, int(round(movement.pos.x)), int(round(movement.pos.y)),
                gameObject.w, gameObject.h, texOffX, 0, gameObject.w, gameObject.h);
        }
        renderer.present();
        /* End Rendering */

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
