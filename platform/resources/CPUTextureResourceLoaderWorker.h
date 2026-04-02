#ifndef CPU_TEXTURE_RESOURCE_LOADER_WORKER_H
#define CPU_TEXTURE_RESOURCE_LOADER_WORKER_H

#include <queue>
#include <thread>
#include <shared_mutex>
#include <filesystem>

#include "core/datastructures/FreeList.h"
#include "core/identity/Id.h"
#include "core/identity/IdGenerator.h"

#include "CPUTextureHandle.h"
#include "CPUTextureResourceLoader.h"

namespace Platform::Resources {

/// Ok, soo the idea here is that we have a single thread that loads textures.
/// This means that we need some kind of job queue in order to keep track of 
/// which job has been completed.
/// Call this class' methods from the same thread, usually the main thread.
/// I am not sure whether this will be the case forever....I have to use the class more,
/// to know for certain.
class CPUTextureLoadWorker : public CPUTextureResourceLoader {
public:
	/// Starts the worker thread.
	CPUTextureLoadWorker();

	// Note: It would be cool to have the loader have a way to reference
	// textures via path too...sometimes we want to resolve by Id, but sometimes
	// we know which texture we want and we know the file name...
	// Or what if we can hash the file name into a Id and use this Id.....
	// That would be ballsack-cool, but i think we are getting ahead of ourselves.
	// This method is not thread-safe, call it consequtively.
	// Its very fast and cheap so no need to call it from multiple threads.
	IdOrError load(const std::filesystem::path& texturePath) override;

private:
	class TexLoadJob {
	public:
		explicit TexLoadJob(std::filesystem::path texPath, Core::Identity::Id id) noexcept:
			texPath(std::move(texPath)), allocatedId(id) {}

		const std::filesystem::path& getPath() const noexcept { return texPath; }
		Core::Identity::Id getId() const noexcept { return allocatedId; }
	private:
		const std::filesystem::path texPath; ///< Path to the texture, requested for loading.
		const Core::Identity::Id allocatedId; ///< The id with which the texture will be stored in the free list. This id is pre-generated so we can return it immediately to the caller.
	};

	Core::Identity::IdGenerator idGen; ///< Instance that can generate ids for the textures. Should be called from a single-threaded context.
	std::queue<TexLoadJob> jobQueue; ///< Buffers incoming load commands, so they can be executed later, when the thread is available.
	std::shared_mutex jobQueueMutex; ///< Guards the job queue from concurrent access.
	Core::DataStructures::FreeList<CPUTextureHandle> texHandleFreeList; ///< Actual storage of the CPU texture handles.
	std::shared_mutex freeListMutex; ///< Guards the freelist from concurrent access. Might be worth implementing this inside a wrapper container so we don't repeat the synchronization logic.
	std::jthread workerThread; ///< This thread polls from the job queue and executes texture loading commands.
};

}

#endif // !SDL_CPU_TEXTURE_LOADER_ASYNC_H
