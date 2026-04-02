#include "CPUTextureResourceLoaderWorker.h"

using namespace Platform::Resources;

CPUTextureLoadWorker::CPUTextureLoadWorker()
{
	workerThread = std::jthread([this]() {
		// What is the jist of the worker thread?
		// 1. we need some synchronization (read-write?) because 
		// the "load" method will add to the queue and this thread will read from it.
		// 2. We do the actual loading - this is specific to the implementation
		// so maybe we need an interface or a strategy pattern for the loading method
		// It will accept a path and it will return a CPUTextureHandle, which is pretty generic.
		// 3. At the end we need to add to the freeList BUT we need synchronization again
		// because this thread will write into the freeList and other threads will read/write
		// for example "resolve", "remove" methods, etc.
		
		// Note: We don't want the thread to be spinning forever...
		// Lets think of a way to make it pausable...
		// For example, we load the textures we want and then we put the thread on pause mode.
		// It will not spin or consume resources, the scheduler will park it.
		// Later when we want to load resources again we say, resume() and we can ask for resources
		// again.
	});
}

IdOrError Platform::Resources::CPUTextureLoadWorker::load(const std::filesystem::path& texturePath)
{
	TexLoadJob job{ .texPath = texturePath, .allocatedId = idGen.next() };
	{
		std::unique_lock lock(jobQueueMutex);
		jobQueue.push(job);
	}
	return job.allocatedId;
}
