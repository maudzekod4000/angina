#ifndef SDL_GRAPHICS_ENGINE_H_
#define SDL_GRAPHICS_ENGINE_H_

#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>

#include "SDL_events.h"
#include "SDL_ttf.h"

#include "platform/sdl/events/InputEvent.h"
#include "platform/sdl/primitives/Font.h"
#include "platform/sdl/components/Window.h"

#include "renderer/primitives/Dimensions.h"
#include "renderer/primitives/Point.h"
#include "renderer/Renderer.h"

#include "engine/factory/GraphicsFactory.h"
#include "engine/behaviour/Behaviour.h"
#include "engine/movement/LinearFixedMovementManager.h"
//#include "managers/EventManager.h"
//#include "managers/EventManager.h"
#include "platform/sdl/repositories/TextureRepository.h"
#include "platform/sdl/repositories/SurfaceRepository.h"

struct Texture;
struct Rect;
struct Object;
struct Screen;
struct Line;
struct Grid;
struct RectTextButton;
struct FolderGallery;

class Engine {
public:
	Engine(std::string appTitle, Dimensions screenSize);
	virtual ~Engine();

	void start();
private:
	Window window;
	SDL_Event e;
	Renderer renderer;
	SurfaceRepository surfaceRepo;
	TextureRepository textureRepo;
	GraphicsFactory factory;
	Screen* rootScreen;
	LinearFixedMovementManager movementManager;
	bool quit = false;
	std::vector<Behaviour<Object>*> behaviours;

	void limitFPS(int64_t microseconds);
	void draw();
	void draw(Screen&);
	void handleEvent();
	void triggerObjectStart();
	void triggerObjectUpdate();
protected:
	InputEvent event;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void handleLeftMouseClick(Point) = 0;
	virtual void handleBtnClick(int32_t idx) = 0;

	void resizeWindow(Dimensions dim);

	void initialiseScreen();
	void addComponent(Object&);
	void addComponent(Line&);
	void addComponent(Grid&);
	void addComponent(RectTextButton&);
	void addComponent(FolderGallery&);
	void cleanScreen();

	void initMapBuilder();

	void addBehaviour(Behaviour<Object>&);
	void addMovement(Object& obj);

	GraphicsFactory& getFactory();
};

#endif /* SDL_GRAPHICS_ENGINE_H_ */
