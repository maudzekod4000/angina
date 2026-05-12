#ifndef PLATFORM_RENDERER_H
#define PLATFORM_RENDERER_H

#include <memory>

#include "platform/resources/TextureHandle.h"

namespace Platform::Rendering {

/// Different implementations will override these methods
/// and implement different kinds of render engines like SDL.
class Renderer {
public:
	virtual void render(Platform::Resources::TextureHandle) = 0;
};

using RendererPtr = std::shared_ptr<Platform::Rendering::Renderer>;

}

#endif // !PLATFORM_RENDERER_H
