#include "Engine.h"

#include <vector>
#include <string>
#include <iostream>

#include "platform/sdl/primitives/Texture.h"
#include "platform/sdl/primitives/Surface.h"
#include "platform/sdl/resource-loader/ResourceLoader.h"
#include "platform/thread/ThreadUtils.h"
#include "platform/time/Time.h"

#include "resources/Resources.h"

#include "renderer/primitives/Color.h"
#include "renderer/shapes/Rect.h"
#include "renderer/primitives/Object.h"
#include "renderer/primitives/Button.h"
#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"
#include "renderer/primitives/Line.h"
#include "renderer/primitives/Grid.h"

#include "engine/config/EngineConfig.h"
#include "engine/screen/Screen.h"
#include "engine/components/buttons/RectTextButton.h"
#include "engine/components/foldergallery/FolderGallery.h"

Engine::Engine(std::string appTitle, Dimensions screenSize) :
		window(Window(
		        appTitle,
		        { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED },
		        { screenSize.w, screenSize.h },
				SDL_WINDOW_SHOWN
			  )),
        renderer(Renderer(window)),
        surfaceRepo(SurfaceRepository()),
        textureRepo(TextureRepository(surfaceRepo, renderer)),
        factory(GraphicsFactory(renderer, textureRepo)),
        rootScreen(nullptr) {

	event.init();
	initialiseScreen();
}

void Engine::start() {
	init();
	triggerObjectStart();
	Time globalTime;
	Time movementUpdateTime;


	while (!quit) {
		globalTime.getElapsed();

		renderer.clear();

		while (event.poll()) {
			if (event.hasExitEvent()) {
				quit = true;
				break;
			}

			handleEvent();
		}

		update();
		triggerObjectUpdate();
		int64_t movementUpdateTimePassed = movementUpdateTime.getElapsed().toMicroseconds();
		movementManager.processFrame(movementUpdateTimePassed);
		movementUpdateTime.getElapsed();

		draw();

		renderer.update();

		int64_t timePassed = globalTime.getElapsed().toMicroseconds();

		limitFPS(timePassed);
	}
}

void Engine::draw() {
	if (rootScreen != nullptr) {
		draw(*rootScreen);
	}
}

void Engine::draw(Screen &widget) {
	for (auto const &drawable : widget.getDrawables()) {
		drawable->draw(renderer);
	}
}

void Engine::limitFPS(int64_t elapsedTime) {
	const int64_t maxFrames = EngineConfig::FRAME_RATE;
	const int64_t timeForFrameMicro = 1000000 / maxFrames;
	const int64_t sleepTime = timeForFrameMicro - elapsedTime;

	if (sleepTime <= 0) {
		return;
	}

	ThreadUtils::sleepFor(sleepTime);
}

void Engine::handleEvent() {
	//btnManager.invokeCallback(event);
}

void Engine::triggerObjectStart() {
	for (Behaviour<Object>* behaviour : behaviours) {
		behaviour->start();
	}
}

void Engine::triggerObjectUpdate() {
	for (Behaviour<Object>* behaviour : behaviours) {
		behaviour->update();
	}
}

GraphicsFactory& Engine::getFactory() {
	return factory;
}

void Engine::initialiseScreen() {
	cleanScreen();

	rootScreen = new Screen();
}

void Engine::addComponent(Object& obj) {
	 rootScreen->put(dynamic_cast<Drawable&>(obj));
}

void Engine::addComponent(Line& line) {
	rootScreen->put(dynamic_cast<Drawable&>(line));
}

void Engine::addComponent(RectTextButton& btn) {
	//btnManager.registerButton(btn);
	rootScreen->put(dynamic_cast<Drawable&>(btn));
}

void Engine::addComponent(Grid& grid) {
	rootScreen->put(dynamic_cast<Drawable&>(grid));
}

void Engine::addComponent(FolderGallery& gallery) {
	rootScreen->put(dynamic_cast<Drawable&>(gallery));
}

void Engine::addBehaviour(Behaviour<Object>& behaviour) {
	behaviour.setEngine(*this);
	behaviours.push_back(&behaviour);
}

void Engine::addMovement(Object& obj) {
    movementManager.addMoveable(obj);
}

void Engine::cleanScreen() {
	if (rootScreen != nullptr) {
		delete rootScreen;
		rootScreen = nullptr;
	}
}

void Engine::initMapBuilder() {
	initialiseScreen();
	resizeWindow(EngineConfig::MB_DIM);

	Object& bg = getFactory().createObject(Resources::MapBuilder::background, Point::ZERO, EngineConfig::MB_DIM);
	addComponent(bg);

	Grid& textureGrid = *new Grid(Point::ZERO, EngineConfig::TILE_DIM, 800, 640);
	addComponent(textureGrid);

	// Move this as parameter to the method and get it from the game.
	std::vector<std::string> textureList = {Resources::TD::grass};

	FolderGallery& gallery = *new FolderGallery(
			Point {801, 0},
			getFactory(),
			textureList,
			1,
			1,
			EngineConfig::TILE_DIM
	);

	addComponent(gallery);
}

void Engine::resizeWindow(Dimensions dim) {
	window.resize(dim);
}

Engine::~Engine() {
	cleanScreen();
	event.deinit();

	std::cout << "Engine destroyed" << std::endl;
}
