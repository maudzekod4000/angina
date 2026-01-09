#include "FolderGallery.h"

#include "engine/factory/GraphicsFactory.h"
#include "renderer/Renderer.h"

FolderGallery::FolderGallery(
		Point pos,
		GraphicsFactory& fac,
		std::vector<std::string> imageFileNames,
		[[maybe_unused]]int32_t rows,
		[[maybe_unused]]int32_t cols,
		Dimensions dim
): factory(fac) {
	int32_t row = 0;

	for (std::string& imageFileName : imageFileNames) {
		// Puts the images on top of each other.
		Object& image = factory.createObject(
				imageFileName,
				pos + Point {0, static_cast<float>(static_cast<int32_t>(dim.h) * row)},
				dim
		);
		images.push_back(&image);
		row++;
	}
}

void FolderGallery::draw(Renderer& renderer) {
	for (Object* image : images) {
		renderer.render(*image);
	}
}
