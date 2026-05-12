#ifndef PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
#define PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H

#include <expected>

#include "core/error/Errors.h"
#include "platform/resources/TextureHandle.h"

namespace Platform::Resources {
class TextureTransferer {
public:
	virtual std::expected<Platform::Resources::TextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(Platform::Resources::TextureHandle) = 0;
};
}

#endif // !PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
