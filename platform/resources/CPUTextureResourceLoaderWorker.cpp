#include "CPUTextureResourceLoaderWorker.h"

using namespace Platform::Resources;
using namespace Core::Errors;

CPUTextureLoadWorker::CPUTextureLoadWorker(LoadTextureFunc loadTextureFunc)
{
	working = true;
	workerThread = std::jthread([loadTextureFunc, this]() {
		// What is the jist of the worker thread?
		// 1. we need some synchronization (read-write?) because 
		// the "load" method will add to the queue and this thread will read from it.
		// This code is not designed to be executed in several threads
		// the idea is that we want a single thread to load all texture resources.
		// I haven't checked if its okay to run this in a loop for example.
		while (working) {
			TexLoadJob job;
			{
				const std::shared_lock readLock(jobQueueMutex);
				if (jobQueue.empty()) {
					// A better pattern would be to use a std::condition_variable.
					// This spins and locks/unlocks the read lock too often.
					continue;
				}
				job = jobQueue.front();
			}
			
			{
				const std::unique_lock writeLock(jobQueueMutex);
				jobQueue.pop();
			}
			// 2. We do the actual loading - this is specific to the implementation
			// so maybe we need an interface or a strategy pattern for the loading method
			// It will accept a path and it will return a CPUTextureHandle, which is pretty generic.
			const CPUTextureHandle tex = loadTextureFunc(job.getPath());
			// 3. At the end we need to add to the freeList BUT we need synchronization again
			// because this thread will write into the freeList and other threads will read/write
			// for example "resolve", "remove" methods, etc.
			const std::unique_lock freeListLock(freeListMutex);
			texHandleFreeList.add(job.getId(), tex);
		}
		
		// Note: We don't want the thread to be spinning forever...
		// Lets think of a way to make it pausable...
		// For example, we load the textures we want and then we put the thread on pause mode.
		// It will not spin or consume resources, the scheduler will park it.
		// Later when we want to load resources again we say, resume() and we can ask for resources
		// again.
	});
}

CPUTextureLoadWorker::~CPUTextureLoadWorker()
{
	working = false;
}

IdOrError CPUTextureLoadWorker::load(const std::filesystem::path& texturePath)
{
	const auto id = idGen.next();
	{
		const std::unique_lock lock(jobQueueMutex);
		jobQueue.emplace(texturePath, id);
	}
	return id;
}

std::vector<IdOrError> CPUTextureLoadWorker::load(const std::vector<std::filesystem::path>& resourceFiles)
{
	const std::unique_lock lock(jobQueueMutex);
	std::vector<IdOrError> ids;
	
	for (const auto& path : resourceFiles) {
		const auto id = idGen.next();
		ids.push_back(id);
		jobQueue.emplace(path, id);
	}
	
	return ids;
}

ErrorCode CPUTextureLoadWorker::release(Core::Identity::Id id)
{
	const std::unique_lock lock(freeListMutex);
	texHandleFreeList.remove(id);
	return ErrorCode();
}

CPUTextureHandle CPUTextureLoadWorker::resolve(Core::Identity::Id id)
{
	const std::shared_lock lock(freeListMutex);
	return texHandleFreeList.get(id);
}

bool Platform::Resources::CPUTextureLoadWorker::isValid(Core::Identity::Id id)
{
	const std::shared_lock lock(freeListMutex);
	return texHandleFreeList.has(id);
}
