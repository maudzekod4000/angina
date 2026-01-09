#include "GraphicsFactory.h"

#include "platform/sdl/resource-loader/ResourceLoader.h"
#include "platform/sdl/primitives/Surface.h"
#include "renderer/Renderer.h"
#include "renderer/primitives/Object.h"
#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"
#include "platform/sdl/primitives/Font.h"
#include "renderer/primitives/Text.h"
#include "renderer/shapes/Rect.h"
#include "engine/components/buttons/RectTextButton.h"
#include "platform/sdl/repositories/TextureRepository.h"

GraphicsFactory::GraphicsFactory(Renderer &r, TextureRepository& repo):
		renderer(r), textureRepo(repo) {}

Object& GraphicsFactory::createObject(const std::string &resourcePath, Point p, Dimensions dim) {
	return renderer.from(textureRepo.get(resourcePath), p, dim);
}

Text& GraphicsFactory::createText(const std::string textVal, Point p, Dimensions dim) {
	return renderer.fromTexture(textureRepo.get(textVal), p, dim);
}

RectTextButton& GraphicsFactory::createButton(Point p, Dimensions dim,
		Color backgroundColor, std::string text,
		std::function<void(void)> clb) {
	Text *btnText = &GraphicsFactory::createText(text, p, dim);

	return *new RectTextButton(p, dim, backgroundColor, *btnText, clb);
}

Rect& GraphicsFactory::createRect(Point p, Dimensions dim, Color c) {
	return *new Rect(p, dim, c);
}
