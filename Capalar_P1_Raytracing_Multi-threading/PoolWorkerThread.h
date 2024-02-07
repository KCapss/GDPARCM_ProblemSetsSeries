#pragma once
#include <iostream>
#include <memory>
#include "IETThread.h"

class IWorkerAction;
class IFinishedTask;
/// <summary>
/// A Pool of thread that execute action
/// </summary>
class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finishedTask);
	~PoolWorkerThread();

	int GetThreadID();
	void assignTask(IWorkerAction* action);

private:
	void run() override;

	int id = 0;
	IWorkerAction* action = nullptr;
	//std::shared_ptr<IFinishedTask*> finishedTask;
	IFinishedTask* finishedTask;

};

