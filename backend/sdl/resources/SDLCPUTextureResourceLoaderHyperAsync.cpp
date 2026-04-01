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
    }).detach(); // By changing this to join, the code works...so its a concurrency issue with FreeList.
    // Which is super weird because i have a lock....
    // By the way, I think it would be sufficient if we just spawn a single 
    // thread for loading textures...Or maybe a configurable number of workers to 
    // load textures, maybe sometimes we can have two workers.
    // Ok, back to the issue...we definitely get some kinda concurrency in the FreeList
    // and its state becomes balls....
    // Can't we just use the synchronous class which loads textures and use it in a thread.
    // Or call the load method in a separate thread.
    // Option 1:
    // Have a synchronous class and do something like.
    // MyLoaderClass loader;
    // std::thread([]() { loader.load(....) });
    // But....thats not good because the client has to use synchronization,
    // if the class itself doesnt....
    // Option 2:
    // Have a class that spins a configurable number of workers that 
    // can load textures...
    // MyLoaderClass loader(2);
    // loader.load(...)
    // We do that at the initialization of the game
    // Later we have a bit of waiting for the resource, which should be zero
    // most of the time.
    // Option 3:
    // we can have a class with just one worker for loading textures and also
    // some mechanism for waiting on a texture (spinning a bit).
    // Yeah, I suppose one thread is enough because there will be a lot more things going on...
    // Ok, sooo I will do a single threaded version a bit later....
    // It is useful to add another method to the API which will be like waitIsValid(id)...

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
    std::unique_lock lock(freeListMutex);
    texHandleFreeList.remove(id);
    return ErrorCode();
}

CPUTextureHandle SDLCPUTextureLoaderHyperAsync::resolve(Id id)
{
    std::shared_lock lock(freeListMutex);
    return texHandleFreeList.get(id);
}

bool SDLCPUTextureLoaderHyperAsync::isValid(Id id)
{
    std::shared_lock lock(freeListMutex);
    return texHandleFreeList.has(id);
}
