#include "PoolWorkerThread.h"
#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask)
{
	this->id = id;
	this->finishedTask = finishedTask;

	//std::cout << "Pool Worker thread ID: " << id <<  std::endl;

	

}

PoolWorkerThread::~PoolWorkerThread()
{
	
}

int PoolWorkerThread::GetThreadID()
{
	return this->id;
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->action = action;
}

void PoolWorkerThread::run()
{
	
	bool running = true;
	action->onStartTask();

	finishedTask->onFinished(id);
	//std::cout << "Skip Task threading" << std::endl;
	
}
