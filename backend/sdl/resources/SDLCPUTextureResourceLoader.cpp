#include "SDLCPUTextureResourceLoader.h"

#include <cassert>

#include "SDLCPUTexture.h"

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Core::Identity;
using namespace Core::Errors;
using namespace Platform::Resources;

IdOrError SDLCPUTextureResourceLoader::load(const std::filesystem::path& resourceFile)
{
	assert(!resourceFile.empty());

	// TODO: hmmmmmm okay so we can actually have a parallel I/O loader
	// which will load the files in parallel and then will call IMG_Load_RW
	// in serial because it seems the IMG decoding is not thread safe in SDL...
	// So this method will be kinda redundant...anyway leave it for now and add a new method
	// that will accept a list of resource files.
	// But idk if the parallel file loader should be implemented here...
	// Maybe another class that can load files in parallel and provide pointers
	// to the data is better.
	// Maybe the freelist can be useful here too.
	// So this method here will accept a...vector of pointers?
	// or maybe it will have a reference to the parallel file loading class and fetch
	// the ids from there? No thats kinda awkward....
	// So at the end it turns out that both the GPU and the CPU decoding can't be 
	// done in parallel hahahhaha so....its kinda funny but anyway....
	SDL_Surface* loadedSurface = IMG_Load((const char*)(resourceFile.u8string().c_str()));

	if (!loadedSurface) {
		// TODO: SDL provides ways to query the system for errors and get a more concrete error msg.
		return std::unexpected(ErrorCode(-1, "Failed to load surface."));
	}

	CPUTextureHandle loadedTexHandle{};
	loadedTexHandle.ptr = new SDLCPUTexture(loadedSurface);
	loadedTexHandle.isReady = true; // Loading surfaces sync right now.

	const Id texId = texHandleFreeList.add(loadedTexHandle);

	return texId;
}

std::vector<IdOrError> SDLCPUTextureResourceLoader::load(const std::vector<std::filesystem::path>& resourceFiles)
{
	std::vector<IdOrError> results;
	results.reserve(resourceFiles.size());

	for (const auto& resPath : resourceFiles) {
		results.push_back(load(resPath));
	}

	return results;
}

ErrorCode SDLCPUTextureResourceLoader::release(Core::Identity::Id id)
{	
	texHandleFreeList.remove(id);

	return ErrorCode();
}

CPUTextureHandle SDLCPUTextureResourceLoader::resolve(Core::Identity::Id id)
{
	return texHandleFreeList.get(id);
}

bool SDLCPUTextureResourceLoader::isValid(Core::Identity::Id id)
{
	return texHandleFreeList.has(id);
}
