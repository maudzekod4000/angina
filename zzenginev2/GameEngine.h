#ifndef ENGINEV2_GAMEENGINE_H_
#define ENGINEV2_GAMEENGINE_H_

#include <string>
#include <cstdint>
#include <memory>

#include "enginev2/graphics/sdl/window/Window.h"
#include "enginev2/events/GlobalInputComponent.h"
#include "enginev2/components/AnimationComponent.h"
#include "enginev2/graphics/sdl/renderer/TextureRendererComponent.h"
#include "enginev2/graphics/sdl/renderer/TextureLoaderComponent.h"
#include "enginev2/movement/MovementCmpt.h"
#include "enginev2/collisions/CollisionDetector.h"
#include "enginev2/components/PrimitivesStorage.h"
#include "enginev2/graphics/sdl/primitives/Rectangle.h"
#include "enginev2/graphics/animation/SpriteAnimator.h"

class GameEngine {
public:
  GameEngine() = default;
	GameEngine(const std::string& appTitle, int32_t width, int32_t height);
	virtual ~GameEngine() = default;

	void init(const std::string& appTitle, int32_t width, int32_t height);
	void start();

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void handleEvent() = 0;

	/// <summary>
	/// Always check the vector size before accessing elements - it could be empty.
	/// </summary>
	virtual void handleCollisions(std::vector<CollisionData>) = 0;

	void drawGPU();
protected:
	PrimitivesStorage<Rectangle> rectangleComponent;
  PrimitivesStorage<GameObject> objectComponent;
	PrimitivesStorage<Texture> textureComponent;
	SpriteAnimator spriteAnimator;
  //AnimationComponent animationComponent;
	GlobalInputComponent inputComponent;
	MovementCmpt movementComponent;
	CollisionDetector collisionDetector;
	// TODO: Extract the helper method into a class and add it here so a client can easily namespace-use methods
	std::shared_ptr<Texture> loadTexture(const std::string& resourcePath);

	void setClearColor(const Color&);
	void setTargetFrameRate(float fr);
private:
	Window win;
	TextureRendererComponent textureRenderer;
	bool gameOver = false;
	float targetFrameRate = 60;
	float frameDurationMs = 1000 / targetFrameRate;
};

#endif /* ENGINEV2_GAMEENGINE_H_ */
