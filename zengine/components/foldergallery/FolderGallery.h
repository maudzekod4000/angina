#ifndef ENGINE_COMPONENTS_FOLDERGALLERY_FOLDERGALLERY_H_
#define ENGINE_COMPONENTS_FOLDERGALLERY_FOLDERGALLERY_H_

#include <vector>
#include <string>
#include <cstdint>

#include "renderer/primitives/Point.h"
#include "renderer/drawable/Drawable.h"
#include "renderer/primitives/Dimensions.h"

struct Object;
struct GraphicsFactory;
struct Renderer;

class FolderGallery : public Drawable {
public:
	FolderGallery(Point pos, GraphicsFactory&, std::vector<std::string> imageFileNames, int32_t rows, int32_t cols, Dimensions dim);

	void draw(Renderer&);
private:
	std::vector<Object*> images;
	GraphicsFactory& factory;
};

#endif /* ENGINE_COMPONENTS_FOLDERGALLERY_FOLDERGALLERY_H_ */
