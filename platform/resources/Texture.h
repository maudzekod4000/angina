#ifndef RESOURCES_TEXTURE_H
#define RESOURCES_TEXTURE_H

namespace Platform::Resources {

struct Texture {
	virtual ~Texture() {}

	virtual int width() const { return 0; }

	virtual int height() const { return 0; }
};

}

#endif // !RESOURCES_TEXTURE_H
