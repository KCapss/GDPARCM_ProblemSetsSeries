#include "ThreadPool.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numWorkers) : IETThread()
{
	this->name = name;
	this->numWorker = numWorkers;

	for (int i = 0; i < this->numWorker; i++) {
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
	this->stopStartScheduler();
	this->activeThreads.clear();
	while (this->inactiveThreads.empty() == false) {
		this->inactiveThreads.pop();
	}
}

void ThreadPool::startScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::stopStartScheduler()
{
	this->running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
	//std::cout << "New Task" << std::endl;
}

void ThreadPool::run()
{
	while (this->running) {
		if (this->pendingActions.empty() == false) {
			if (this->inactiveThreads.empty() == false) {

				
				//Schedule the task;
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->GetThreadID()] = workerThread;

				workerThread->assignTask(this->pendingActions.front());
				workerThread->start();
				this->pendingActions.pop();

			}

			else {
				//std::cout << "Pending Task Found" << std::endl;
			}
		}

		else {
			//std::cout << "[ThreadPool " << this->name << "]" << "No action scheduled" << std::endl;
			

		}

		for (int i = 0; i < numWorker; i++) {
			//this->onFinished(i);
		}
		
	}
}

void ThreadPool::onFinished(int threadID)
{
	if (this->activeThreads[threadID] != nullptr) {

		//create a fresh instance of a thread worker after execution
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));
	}

}
