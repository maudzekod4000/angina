#ifndef RESOURCES_IRESOURCE_LOADER_H
#define RESOURCES_IRESOURCE_LOADER_H

#include <filesystem>

#include "core/identity/Id.h"
#include "CPUTextureHandle.h"
#include "core/error/Errors.h"

namespace Platform::Resources {
/// Interface for loading and releasing resources. Lifetime interface.
class CPUTextureResourceLoader {
public:
	/// Loads a resource from disk into memory.
	/// @param resourceFile File path to the resource.
	/// @return The id of the resource. Can be used to get a handle to the resource.
	virtual Core::Identity::Id load(const std::filesystem::path& resourceFile) = 0;

	/// Frees the memory allocated for the resource.
	/// @param id Same id that was returned from 'load' when the resource was allocated.
	/// @return Non-empty error object if there was an error during release of resource.
	virtual Core::Errors::ErrorCode release(Core::Identity::Id id) = 0;

	/// Looks for a texture with the provided id and returns a handle to it, if it exists.
	/// @param id The id of the required texture.
	/// @return Returns a handle to the texture.
	virtual CPUTextureHandle resolve(Core::Identity::Id id) = 0;

	virtual ~CPUTextureResourceLoader() = default;
};
}

#endif // !RESOURCES_IRESOURCE_LOADER_H
