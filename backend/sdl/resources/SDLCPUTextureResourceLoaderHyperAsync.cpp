#include "SDLCPUTextureResourceLoaderHyperAsync.h"

#include "SDL_image.h"

#include "backend/sdl/resources/SDLCPUTexture.h"

using namespace Backend::SDL::Resources;
using namespace Core::Identity;
using namespace Core::Errors;
using namespace Platform::Resources;

IdOrError SDLCPUTextureLoaderHyperAsync::load(const std::filesystem::path& resourceFile)
{
    // The idea here is that we will detach the thread that fetches the resource
    // We will let it add to the freelist with some locking (or lock free?)
    // We will return an id immediately. Errors are a bit tricky...maybe we ignore them for now.

    auto id = idGenerator.next();

    std::thread([id, resourceFile, this]() {
        SDL_Surface* surface = IMG_Load((const char*)(resourceFile.u8string().c_str()));

        if (surface) {
            CPUTextureHandle loadedTexHandle{};
		    loadedTexHandle.ptr = new SDLCPUTexture(surface);
		    loadedTexHandle.isReady = true;

            // sync block
            {
                std::unique_lock lock(freeListMutex);
		        texHandleFreeList.add(id, loadedTexHandle);
            }
        }
    }).detach();

    return id;
}

std::vector<Platform::Resources::IdOrError> Backend::SDL::Resources::SDLCPUTextureLoaderHyperAsync::load(const std::vector<std::filesystem::path>& resourceFiles)
{
    return std::vector<Platform::Resources::IdOrError>();
}

Core::Errors::ErrorCode Backend::SDL::Resources::SDLCPUTextureLoaderHyperAsync::release(Core::Identity::Id id)
{
    return Core::Errors::ErrorCode();
}

Platform::Resources::CPUTextureHandle Backend::SDL::Resources::SDLCPUTextureLoaderHyperAsync::resolve(Core::Identity::Id id)
{
    return Platform::Resources::CPUTextureHandle();
}

bool Backend::SDL::Resources::SDLCPUTextureLoaderHyperAsync::isValid(Core::Identity::Id id)
{
    return false;
}
