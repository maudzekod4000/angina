#ifndef RESOURCES_IRESOURCE_LOADER_H
#define RESOURCES_IRESOURCE_LOADER_H

#include <filesystem>

#include "core/identity/Id.h"
#include "core/error/Errors.h"

namespace Platform::Resource {
/// Interface for loading and releasing resources. Lifetime interface.
class IResourceLoader {
public:
	/// Loads a resource from disk into memory.
	/// @param resourceFile File path to the resource.
	/// @return The id of the resource. Can be used to get a handle to the resource.
	virtual Core::Identity::Id load(const std::filesystem::path& resourceFile) = 0;

	/// Frees the memory allocated for the resource.
	/// @param id Same id that was returned from 'load' when the resource was allocated.
	/// @return Non-empty error object if there was an error during release of resource.
	virtual Core::Errors::ErrorCode release(Core::Identity::Id id) = 0;

	virtual ~IResourceLoader() = default;
};
}

#endif // !RESOURCES_IRESOURCE_LOADER_H
