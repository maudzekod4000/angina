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

    // A thread per texture is not ideal. Threads are expensive and image loading is mostly I/O.
    // Meaning that the CPU is not utilized. But there is a lot of context switching.
    workerHandles.push_back(std::jthread([id, resourceFile, this]() {
        // Hahhahah sooo why does this class have to be called SDLSomethingSomething?
        // Just a small snippet is SDL related,
        // we can accept a callback (strategy) which will return a CPUTextureHandle...
        // Anyway I won't refactor the existing methods as they are not optimal anyway.
        SDL_Surface* surface = IMG_Load((const char*)(resourceFile.u8string().c_str()));

        if (surface) {
            CPUTextureHandle loadedTexHandle{};
		    loadedTexHandle.ptr = new SDLCPUTexture(surface);
		    loadedTexHandle.isReady = true;

            texHandleFreeList.write([id, &loadedTexHandle](auto& list) {
                list.add(id, loadedTexHandle);
            });
        }
    }));

    return id;
}

std::vector<IdOrError> SDLCPUTextureLoaderHyperAsync::load(const std::vector<std::filesystem::path>& resourceFiles)
{
    // There won't be errors, for now.
    std::vector<IdOrError> result;

    for (const auto& path : resourceFiles) {
        result.push_back(load(path));
    }

    return result;
}

ErrorCode SDLCPUTextureLoaderHyperAsync::release(Id id)
{
    texHandleFreeList.write([id](auto& list) {
        list.remove(id);
    });
    return ErrorCode();
}

CPUTextureHandle SDLCPUTextureLoaderHyperAsync::resolve(Id id)
{
    return texHandleFreeList.read([id](auto& list) {
        return list.get(id);
    });
}

bool SDLCPUTextureLoaderHyperAsync::isValid(Id id)
{
    return texHandleFreeList.read([id](auto& list) {
        return list.has(id);
    });
}
