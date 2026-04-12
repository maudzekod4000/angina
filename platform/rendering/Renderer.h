#ifndef PLATFORM_RENDERER_H
#define PLATFORM_RENDERER_H

#include "platform/resources/GPUTextureHandle.h"

namespace Platform::Rendering {

/// Different implementations will override these methods
/// and implement different kinds of render engines like SDL.
class Renderer {
public:
	virtual void render(Platform::Resources::GPUTextureHandle) = 0;
};
}

#endif // !PLATFORM_RENDERER_H
