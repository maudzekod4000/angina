#include "CPUTextureResourceLoaderWorker.h"

#include <iostream>
#include <ctime>

using namespace Platform::Resources;
using namespace Core::Errors;

CPUTextureLoadWorker::CPUTextureLoadWorker(LoadTextureFunc loadTextureFunc)
{
	looping = true;
	workerThread = std::jthread([loadTextureFunc, this]() {
		// What is the jist of the worker thread?
		// 1. we need some synchronization (read-write?) because 
		// the "load" method will add to the queue and this thread will read from it.
		// This code is not designed to be executed in several threads
		// the idea is that we want a single thread to load all texture resources.
		// I haven't checked if its okay to run this in a loop for example.
		while (looping) {
			auto cpuStartTime = std::clock();
			TexLoadJob job;
			{
				std::unique_lock waitOnWorkLock(waitOnWorkMutex);
				waitOnWorkSignal.wait(waitOnWorkLock, [this]() {
					return waiting == false;
				});
				waitOnWorkLock.unlock();

				const std::shared_lock readLock(jobQueueMutex);

				if (jobQueue.empty()) {
					// When the thread is stopped, there won't be any
					// work but it is also not waiting anymore
					// so we might get to this point
					break;
				}
				job = jobQueue.front();
			}
			
			{
				const std::unique_lock writeLock(jobQueueMutex);
				jobQueue.pop();

				std::lock_guard updateWaitingLock(waitOnWorkMutex);
				waiting = jobQueue.empty();
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
			auto cpuEndTime = std::clock();

			std::cout << "CPU time per iteration: " <<
				double(cpuEndTime - cpuStartTime) / CLOCKS_PER_SEC <<
				std::endl;
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
	{
		const std::lock_guard lock(waitOnWorkMutex);
		waiting = false;
	}
	waitOnWorkSignal.notify_one();
	looping = false;
}

IdOrError CPUTextureLoadWorker::load(const std::filesystem::path& texturePath)
{
	const auto id = idGen.next();
	{
		const std::unique_lock lock(jobQueueMutex);
		jobQueue.emplace(texturePath, id);
	}
	{
		const std::lock_guard lock(waitOnWorkMutex);
		waiting = false;
	}
	waitOnWorkSignal.notify_one();
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
	{
		const std::lock_guard waitLock(waitOnWorkMutex);
		waiting = false;
	}
	waitOnWorkSignal.notify_one();
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

bool CPUTextureLoadWorker::isValid(Core::Identity::Id id)
{
	const std::shared_lock lock(freeListMutex);
	return texHandleFreeList.has(id);
}
