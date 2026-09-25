#include "Engine.h"

#include <cmath>

#include "backend/sdl/resources/SDLTexLoader.h"
#include "backend/sdl/init/SDLVideoLifecycleManager.h"
#include "core/physics/PhysicsUtils.h"

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
        assert(false);
        return SDLTexture(); // TODO: Return a proper error, so that the client knows it failed
        // or better -> load a default texture for maximum UX or Dev Ex
        // This default texture will be loaded when the engine starts and cached in the 
        // Engine as a field.
    }

    textures.push_back(tex);
    return tex;
}

Resources::AudioEffect Engine::loadSoundEffect(const char* filepath)
{
    using namespace Backend::SDL::Resources;

    ErrorCode err;
    AudioEffect audio = loadAudioEffect(filepath, err);

    if (err) {
        logger.log(Level::ERROR, err);
        assert(false);
        return Resources::AudioEffect(); // TODO: return a default effect
    }

    audioEffects.push_back(audio);
    return audio;
}

void Engine::beforeGameLoop()
{
    Resources::AudioEffect someEffect = loadSoundEffect("resources/engine/scratch.wav");
    Resources::SDLTexture stickfigureTex = loadTexture("resources/engine/stickfigure.png");
    Resources::SDLTexture ballsTex = loadTexture("resources/engine/balls.png");
    // Sometimes we will use the original texture's w/h but sometimes we need to overwrite it.
    // TODO: Hmmm...soo the creation of the object needs to be thought out
    // but lets just do manual creation and then we will see the patterns in the 
    // creation and we will adjust.
    GameObject stickfigure{stickfigureTex, 64, 205};
    stickfigure.flip = 0x1;
    gameObjects.push_back(stickfigure);

    Animation stickAnim(4);
    animations.push_back(stickAnim);

    Movement stickMov;
    //stickMov.start(300, 200, 150);
    movements.push_back(stickMov);
    inputEventMgr.onClickHandler = [this](int x, int y) {
        movements[0].start(x, y, 150);
    };

    // TODO: Hmmm the std::function is 64 bytes and it expands the Movement
    // object too much in size.
    // Maybe we need some system that can check the state of the movement
    // and dispatch additional actions when it starts/finishes.
    movements[0].onMovementStart = [this]() {
        animations[0].start(1000);
        audioEffects[0].play();
    };
    // TODO: So for the movement thing, we can create a MovementObservable
    // that will take care of registering subscribers and the Movement object 
    // will hold a reference to it, so it can notify subscribers for events.
    // ...idk it seems that i dont want to complicate things RN
    movements[0].onMovementEnd = [this]() {
        animations[0].stop();
        audioEffects[0].stop();
    };

    Collision stickCollision{};
    collisions.push_back(stickCollision);

    GameObject balls{ ballsTex, 200, 200 };
    gameObjects.push_back(balls);

    // TODO: It would be nice to have just a simple method that creates
    // one element into all the needed vectors, and after that i can populate what i want
    // For this to be easy, we need default constructors and ability to set things later.
    // Although, I would not put much emphasis on these factory methods.
    Animation ballsAnim(1);
    animations.push_back(ballsAnim);

    Movement ballsMov(300, 300);
    movements.push_back(ballsMov);

    Collision ballsCollision{};
    collisions.push_back(ballsCollision);

    // How can we start thinking about separating the animation
    // and movement on separate threads.
    // soo for instance, the animation does not have new data every frame
    // most often, the texture we render is the same among 20-30 frames
    // that means that the animation requires a bigger update interval, like
    // 24 ms
    // The movement requires a more refined interval..maybe 10 ms?
    // and collisions require the smallest interval, like 5 ms.

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
    if (const auto err = Init::initSDLSystems(0); err) {
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

        /* Collisions */

        // TODO: Think: Soo if we want the collisions to run on a separate thread
        // it would be better to make a separate struct/state for them
        // This means we should update all 'bounding boxes' on every loop iteration, so
        // that the collision system has the freshest data.
        // The collision resolution will read the collision state of the objects and 
        // make changes to the movement of the objects.

        // So if I copy the data into a Collision object that is a write
        // it will happen on every update of the movement system (possibly another thread too)
        // If i decide not to copy the data, then i have to read it.
        // so I would say the movement has to be processed with the fastest rate.
        // Sooo refresh rate (starting from smallest to largest)
        // 1. movement
        // 2. collisions
        // 3. animation
        // 4. rendering
        for (int i = 0; i < gameObjects.size(); i++) {
            for (int j = i + 1; j < gameObjects.size(); j++) {
                const GameObject& a = gameObjects[i];
                const Movement& am = movements[i];
                const GameObject& b = gameObjects[j];
                const Movement& bm = movements[j];
                Collision& colA = collisions[i];
                Collision& colB = collisions[j];

                bool collided = Core::PhysicsUtils::rectIntersect(am.pos.x,
                    -am.pos.y, float(a.w), float(a.h), bm.pos.x, -bm.pos.y, float(b.w), float(b.h));
                    
                colA.hasCollision = colB.hasCollision = collided;
                if (collided) {
                    colA.dir = am.dir;
                    colB.dir = bm.dir;
                    printf("Chestit sbor! %d\n", rand());
                }
            }
        }
        // TODO: It would be nice to have some measurements at this point 
        // so we can keep track how things are affected while adding features and processing more objects.

        /* End collisions */

        /* Resolve collisions */

        for (int i = 0; i < collisions.size(); i++) {
            if (collisions[i].hasCollision) {
                movements[i].pos = addVec(movements[i].pos, Vec2{ -collisions[i].dir.x, -collisions[i].dir.y });
                movements[i].stop();
                // TODO: I have to decide what data type to use
                // all these conversions are cumbersome.
                //movements[i].start(int(dest.x), int(dest.y), 1500);
            }
        }

        /* End Resolve collisions */

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
                gameObject.w, gameObject.h, texOffX, 0, gameObject.w, gameObject.h, gameObject.flip);
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

    Init::destroySDLSystems();

    return {};
}
