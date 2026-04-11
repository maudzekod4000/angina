#ifndef RESOURCES_GPU_RESOURCE_HANDLE_H
#define RESOURCES_GPU_RESOURCE_HANDLE_H

#include "GPUTexture.h"

namespace Platform::Resources {

// Object handle. Value type that is safe and cheap to copy.
struct GPUTextureHandle {
	GPUTexture* ptr = nullptr; ///< Pointer to the resource. Read-only, do not delete. Always check if it is a live resource before using.
	bool isReady = false; ///< Is the resource loaded.

	void freeMem() {
		if (ptr) {
			delete ptr;
			ptr = nullptr;
		}
	}
};

}

#endif // !RESOURCES_GPU_RESOURCE_HANDLE_H
