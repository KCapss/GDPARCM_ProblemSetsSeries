#include "JobSystem.h"
#include "ThreadPool.h"
#include <mutex>

//a singleton class
JobSystem* JobSystem::sharedInstance = NULL;

JobSystem* JobSystem::getInstance()
{
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new JobSystem();
	}
	return sharedInstance;
}

void JobSystem::initializeJob()
{
	processor_count = std::thread::hardware_concurrency();

	//To have one main thread running
	if(threadPool == nullptr)
		threadPool = new ThreadPool("JobWorker", processor_count - 1); 

	threadPool->startScheduler();
}

ThreadPool* JobSystem::GetThreadPool()
{
	return threadPool;
}

JobSystem::JobSystem()
{

}


