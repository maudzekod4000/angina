#ifndef RESOURCES_TEXTURE_HANDLE_H
#define RESOURCES_TEXTURE_HANDLE_H

#include "Texture.h"

namespace Platform::Resources {

struct TextureHandle {
	Texture* ptr = nullptr; ///< Pointer to the resource. Read-only, do not delete. Always check if it is a live resource before using.

	void freeMem() {
		if (ptr) {
			delete ptr;
			ptr = nullptr;
		}
	}
};

}

#endif // !RESOURCES_TEXTURE_HANDLE_H
