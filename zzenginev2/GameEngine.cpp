#include "GameEngine.h"

#include "enginev2/graphics/models/Dimensions.h"
#include "enginev2/graphics/models/Width.h"
#include "enginev2/graphics/models/Height.h"

#include "enginev2/graphics/sdl/renderer/TextureLoaderComponent.h"
#include "enginev2/debug/Debug.h"
#include "enginev2/platform/time/Time.h"
#include "enginev2/platform/thread/ThreadUtils.h"

GameEngine::GameEngine(const std::string& appTitle, int32_t width, int32_t height)
{
	init(appTitle, width, height);
}

void GameEngine::init(const std::string& appTitle, int32_t width, int32_t height) {
	win.init(appTitle, Width(width), Height(height)); // These Width and Height classes should be enforced to the client
	rectangleComponent.init(100);
	//lineComponent.init(1000);
	inputComponent.init();
	textureRenderer.init(win, Color::BLACK);
	//objectComponent.init(textureLoader);
	textureComponent.init(100);
}

void GameEngine::start() {
  onStart();
	Time stopwatch;

	while (!gameOver) {
		stopwatch.getElapsed();
		bool hasEvents = inputComponent.poll();

		if (inputComponent.hasExitEvent()) {
			break;
		}

		handleEvent();

		spriteAnimator.update();
		movementComponent.update();
		onUpdate();

		handleCollisions(collisionDetector.detectCollisions(objectComponent.elements()));

		drawGPU();

		// Frame rate control
		Time& clockedTime = stopwatch.getElapsed();
		float timeLeftInFrame = frameDurationMs - clockedTime.toMilliseconds();
		ThreadUtils::sleepFor(timeLeftInFrame);
	}
}

void GameEngine::drawGPU() {
	textureRenderer.clear();

	for (Texture& tex : textureComponent.elements()) {
		textureRenderer.render(tex);
	}

	for (Rectangle& rect : rectangleComponent.elements()) {
		textureRenderer.render(rect);
	}

	for (GameObject& obj : objectComponent.elements()) {
	  textureRenderer.render(obj);
	}

	/*for (Sprite& sprite : spriteAnimator.data) {
		textureRenderer.render(sprite);
	}*/

	textureRenderer.update();
}

std::shared_ptr<Texture> GameEngine::loadTexture(const std::string& resourcePath)
{
	SDL_Texture* tx = TextureLoaderComponent::loadTexture(textureRenderer, resourcePath);

	if (!tx) {
		DebugLog.showErrorInfo("loading texture");
	}

	return std::make_shared<Texture>(tx);
}

void GameEngine::setClearColor(const Color& color)
{
	textureRenderer.setClearColor(color);
}

void GameEngine::setTargetFrameRate(float fr)
{
	this->targetFrameRate = fr;
	this->frameDurationMs = 1000 / fr;
}
