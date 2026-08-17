#ifndef RESOURCES_TEXTURE_HANDLE_H
#define RESOURCES_TEXTURE_HANDLE_H

#include "Texture.h"

namespace Platform::Resources {

struct TextureHandle {
	explicit TextureHandle(Texture* ptr) noexcept;

	Texture* ptr = nullptr; ///> Do not manually delete or call freeMem(). Engine takes care of it.

	void freeMem();
};

}

#endif // !RESOURCES_TEXTURE_HANDLE_H
