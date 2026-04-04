#ifndef CPU_TEXTURE_RESOURCE_LOADER_WORKER_H
#define CPU_TEXTURE_RESOURCE_LOADER_WORKER_H

#include <queue>
#include <thread>
#include <shared_mutex>
#include <filesystem>
#include <functional>
#include <atomic>

#include "core/datastructures/FreeList.h"
#include "core/datastructures/RWProtected.h"
#include "core/identity/Id.h"
#include "core/identity/IdGenerator.h"

#include "CPUTextureHandle.h"
#include "CPUTextureResourceLoader.h"

namespace Platform::Resources {

using LoadTextureFunc = std::function<CPUTextureHandle(const std::filesystem::path&)>;

/// Ok, soo the idea here is that we have a single thread that loads textures.
/// This means that we need some kind of job queue in order to keep track of 
/// which job has been completed.
/// Call this class' methods from the same thread, usually the main thread.
/// I am not sure whether this will be the case forever....I have to use the class more,
/// to know for certain.
class CPUTextureLoadWorker : public CPUTextureResourceLoader {
public:
	/// Starts the worker thread.
	CPUTextureLoadWorker(LoadTextureFunc);
	
	/// Sets up the state of the loader so that the worker thread is shutdown gracefully.
	~CPUTextureLoadWorker();
	
	// Note: It would be cool to have the loader have a way to reference
	// textures via path too...sometimes we want to resolve by Id, but sometimes
	// we know which texture we want and we know the file name...
	// Or what if we can hash the file name into a Id and use this Id.....
	// That would be ballsack-cool, but i think we are getting ahead of ourselves.
	IdOrError load(const std::filesystem::path& texturePath) override;

	std::vector<IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	// Maybe haivng a synchronizad FreeList is going to be useful...
	// We are going to use it for loading audio too...
	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	CPUTextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;

	bool isDone() const override;

	void wait() override;
private:
	class TexLoadJob {
	public:
		explicit TexLoadJob(std::filesystem::path texPath, Core::Identity::Id id) noexcept:
			texPath(std::move(texPath)), allocatedId(id) {}

		/// Constructs an empty job.
		explicit TexLoadJob() noexcept :
			TexLoadJob(std::filesystem::path{}, 0) {}

		const std::filesystem::path& getPath() const noexcept { return texPath; }
		Core::Identity::Id getId() const noexcept { return allocatedId; }
	private:
		std::filesystem::path texPath; ///< Path to the texture, requested for loading.
		Core::Identity::Id allocatedId; ///< The id with which the texture will be stored in the free list. This id is pre-generated so we can return it immediately to the caller.
	};

	std::mutex allWorkFinishedMutex; ///< This will be used along with a condition variable to track whether all pending work is finished.
	std::condition_variable allWorkFinishedSignal; ///< This will be signalled when all submitted work is finished.
	// This is very interesting...I think that we should do a notify_one only when we decrement?
	// Also add some asserts that this counter should be >= 0. Otherwise there is some programming error.
	int pendingWorkCount = 0; ///< This will be incremented/decremented when work is added/finished.
	
	std::mutex waitOnWorkMutex; ///< To avoid busy-spinning, use this mutex and a condition variable to implement waiting for work.
	std::condition_variable waitOnWorkSignal; ///< This is kinda like a signal? It signals that there is work? Well, it's a better name than waitOnWorkCv haha.
	bool waiting = true; ///< This is used to park the worker thread while there is no work in the queue.
	
	std::atomic_bool looping = false; ///< Used as a condition flag for the worker loop.
	Core::Identity::IdGenerator idGen; ///< Instance that can generate ids for the textures. Should be called from a single-threaded context.
	std::queue<TexLoadJob> jobQueue; ///< Buffers incoming load commands, so they can be executed later, when the thread is available.
	mutable std::shared_mutex jobQueueMutex; ///< Guards the job queue from concurrent access.
	Core::DataStructures::RWProtected<Core::DataStructures::FreeList<CPUTextureHandle>> texHandleFreeList; ///< Actual storage of the CPU texture handles.
	std::jthread workerThread; ///< This thread polls from the job queue and executes texture loading commands.
};

}

#endif // !SDL_CPU_TEXTURE_LOADER_ASYNC_H
