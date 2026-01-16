#ifndef RESOURCES_RESOURCE_HANDLE_H
#define RESOURCES_RESOURCE_HANDLE_H

#include "ITexture.h"

namespace Platform::Resources {

class TextureHandle {
	ITexture* ptr = nullptr; ///< Pointer to the resource. Read-only, do not delete.
	bool isReady = false; ///< Is the resource loaded.
	// TODO: There is a concept of 'generations' but i am still not familiar with it.
};

}

#endif // !RESOURCES_RESOURCE_HANDLE_H
