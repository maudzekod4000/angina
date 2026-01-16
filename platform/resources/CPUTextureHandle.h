#ifndef RESOURCES_RESOURCE_HANDLE_H
#define RESOURCES_RESOURCE_HANDLE_H

#include "ITexture.h"

namespace Platform::Resources {

// Idea: So the Texture manager has to async load textures from disk to memory and then on update() it should 
// pump the textures to GPU
// Or better yet, another class which will take care of the storage of the textures will upload them to GPU.
class CPUTextureHandle {
	ITexture* ptr = nullptr; ///< Pointer to the resource. Read-only, do not delete.
	bool isReady = false; ///< Is the resource loaded.
	// TODO: There is a concept of 'generations' but i am still not familiar with it.
};

}

#endif // !RESOURCES_RESOURCE_HANDLE_H
