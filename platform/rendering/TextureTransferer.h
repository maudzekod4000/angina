#ifndef PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
#define PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H

#include <expected>

#include 

#include "GPUTextureHandle.h"
#include "CPUTextureHandle.h"

namespace Platform::Resources {
class TextureTransferer {
public:
	virtual std::expected<Platform::Resources::GPUTextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(Platform::Resources::CPUTextureHandle) = 0;
};
}

#endif // !PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
