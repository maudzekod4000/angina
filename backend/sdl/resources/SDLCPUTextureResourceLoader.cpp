#include "SDLCPUTextureResourceLoader.h"

#include <cassert>

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Core::Identity;
using namespace Core::Errors;
using namespace Platform::Resources;

IdOrError SDLCPUTextureResourceLoader::load(const std::filesystem::path& resourceFile)
{
	assert(!resourceFile.empty());

	SDL_Surface* loadedSurface = IMG_Load((const char*)(resourceFile.u8string().c_str()));

	if (!loadedSurface) {
		// TODO: SDL provides ways to query the system for errors and get a more concrete error msg.
		return std::unexpected(ErrorCode(-1, "Failed to load surface."));
	}

	CPUTextureHandle loadedTexHandle{};
	loadedTexHandle.ptr = new SDLCPUTexture(loadedSurface);
	loadedTexHandle.isReady = true; // Loading surfaces sync right now.

	const Id texId = idGenerator.next();
	
	if (freeList.size() > 0) {
		const size_t idx = freeList.top();
		freeList.pop();
		assert(idx >= 0 && idx < storage.size()); // This should not happen, its an invariant for the class.
		storage[idx] = loadedTexHandle;
		idToIndexInStorage[texId] = idx;
	}
	else {
		storage.push_back(loadedTexHandle);
		idToIndexInStorage[texId] = storage.size() - 1;
	}

	return texId;
}

ErrorCode SDLCPUTextureResourceLoader::release(Core::Identity::Id id)
{
	// First, lets find the index of this resource by the id
	auto it = idToIndexInStorage.find(id);

	if (it == idToIndexInStorage.end()) {
		return ErrorCode(-1, "Not found");
	}

	// lets release the resource, mostly the pointer, the structure is already in memory of the vector
	const size_t idx = it->second;

	assert(idx >= 0 && idx < storage.size());

	CPUTextureHandle handle = storage[idx];

	// TODO: Hmm this whole freelist thing can be extracted to its own Data structure.
	if (handle.ptr) {
		delete handle.ptr;
	}

	// add the index to the freelist. Hmmm a stack will make the last released index hot...
	// In case that we have reserve and release one after the other.
	freeList.push(idx);

	return ErrorCode();
}

CPUTextureHandle SDLCPUTextureResourceLoader::resolve(Core::Identity::Id id)
{
	return textureHandlesIndex[id];
}

bool SDLCPUTextureResourceLoader::isValid(Core::Identity::Id id)
{
	return textureHandlesIndex.find(id) != textureHandlesIndex.end();
}
