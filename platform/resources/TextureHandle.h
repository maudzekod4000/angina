#ifndef RESOURCES_TEXTURE_HANDLE_H
#define RESOURCES_TEXTURE_HANDLE_H

#include "Texture.h"

namespace Platform::Resources {

struct TextureHandle {
	explicit TextureHandle(Texture* ptr) noexcept;

	Texture* ptr = nullptr; ///< Pointer to the resource. Read-only, do not delete. Always check if it is a live resource before using.

	void freeMem();
};

}

#endif // !RESOURCES_TEXTURE_HANDLE_H
