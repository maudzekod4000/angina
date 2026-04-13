#ifndef PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
#define PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H

#include <expected>
#include <memory>

#include "core/error/Errors.h"

#include "GPUTextureHandle.h"
#include "CPUTextureHandle.h"

namespace Platform::Resources {
/// Interface for converting a CPU to GPU texture.
class TextureTransferer {
public:
	virtual std::expected<GPUTextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(CPUTextureHandle) = 0;
};

using TextureTransfererPtr = std::unique_ptr<TextureTransferer>;
}

#endif // !PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
