#include "CPUTextureResourceLoaderWorker.h"

#include <iostream>
#include <ctime>

using namespace Platform::Resources;
using namespace Core::Errors;

AsyncTextureLoadWorker::AsyncTextureLoadWorker(LoadTextureFunc loadTextureFunc)
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

			const std::expected<TextureHandle, ErrorCode> texOrErr = loadTextureFunc(job.getPath());

			if (texOrErr.has_value()) {
				const auto tex = texOrErr.value();

				texHandleFreeList.write([&tex, &job](auto& list) {
					list.add(job.getId(), tex);
				});
			}
			else {
				loadErrors.write([&job, &texOrErr](auto& map) {
					map[job.getId()] = texOrErr.error();
				});
			}

			auto cpuEndTime = std::clock();

			std::cout << "CPU time per iteration: " <<
				double(cpuEndTime - cpuStartTime) / CLOCKS_PER_SEC <<
				std::endl;

			std::lock_guard pendingJobsLock(allWorkFinishedMutex);
			pendingWorkCount--;
			allWorkFinishedSignal.notify_one();
		}
	});
}

AsyncTextureLoadWorker::~AsyncTextureLoadWorker()
{
	{
		const std::lock_guard lock(waitOnWorkMutex);
		waiting = false;
	}
	waitOnWorkSignal.notify_one();
	looping = false;
}

IdOrError AsyncTextureLoadWorker::load(const std::filesystem::path& texturePath)
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

	std::lock_guard pendingJobsLock(allWorkFinishedMutex);
	pendingWorkCount++;
	return id;
}

std::vector<IdOrError> AsyncTextureLoadWorker::load(const std::vector<std::filesystem::path>& resourceFiles)
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

	std::lock_guard pendingJobsLock(allWorkFinishedMutex);
	pendingWorkCount += int(resourceFiles.size());

	return ids;
}

ErrorCode AsyncTextureLoadWorker::release(Core::Identity::Id id)
{
	texHandleFreeList.write([id](auto& list) {
		list.remove(id);
	});
	loadErrors.write([id](auto& map) {
		map.erase(id);
	});
	return ErrorCode();
}

TextureHandle AsyncTextureLoadWorker::resolve(Core::Identity::Id id)
{
	return texHandleFreeList.read([id](auto& list) {
		return list.get(id);
	});
}

ErrorCode AsyncTextureLoadWorker::hasError(Core::Identity::Id id)
{
	if (texHandleFreeList.read([id](const auto& list) { return list.has(id); })) {
		return {};
	}
	return loadErrors.read([id](const auto& map) -> ErrorCode {
		auto it = map.find(id);
		if (it != map.end()) return it->second;
		return ErrorCode(1, "Texture not found");
	});
}

bool AsyncTextureLoadWorker::isDone() const
{
	std::shared_lock lock(jobQueueMutex);
	return jobQueue.empty();
}

void AsyncTextureLoadWorker::wait()
{
	// Hmmmmm....
	// So we need a way to track not only whether we are waiting or not
	// or whether the queue has jobs, because then we might return before 
	// the job is completed (polled from queue, but not completed)
	std::unique_lock lock(allWorkFinishedMutex);
	allWorkFinishedSignal.wait(lock, [this]() {
		return pendingWorkCount == 0;
	});
}
