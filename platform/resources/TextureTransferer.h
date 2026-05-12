#ifndef PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
#define PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H

#include <expected>
#include <memory>

#include "core/error/Errors.h"

#include "TextureHandle.h"

namespace Platform::Resources {
/// Interface for converting a CPU to GPU texture.
class TextureTransferer {
public:
	virtual std::expected<TextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(TextureHandle) = 0;

	virtual ~TextureTransferer() = default;
};

using TextureTransfererPtr = std::unique_ptr<TextureTransferer>;
}

#endif // !PLATFORM_RESOURCES_TEXTURE_TRANSFERER_H
