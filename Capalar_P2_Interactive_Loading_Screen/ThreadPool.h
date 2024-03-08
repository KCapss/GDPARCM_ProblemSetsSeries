#pragma once
#include <queue>
#include <unordered_map>
#include "IETThread.h"

class PoolWorkerThread;
class IWorkerAction;
class IFinishedTask {
public:
	virtual void onFinished(int threadID) = 0;
};

/// <summary>
/// Class that holds N workers/threads that can be reused. This is a thread itself, because it only need to constantly scheduled task.
/// </summary>
class ThreadPool: public IETThread, public IFinishedTask
{
private:
	typedef std::string String;
	typedef std::queue<PoolWorkerThread*> ThreadList;
	typedef std::unordered_map<int, PoolWorkerThread*> ActiveThreadMap;
	typedef std::queue<IWorkerAction*> ActionList;

public:
	ThreadPool(String name, int numWorkers);
	~ThreadPool();

	void startScheduler();
	void stopStartScheduler();
	void scheduleTask(IWorkerAction* action);


private:
	void run() override;
	void onFinished(int threadID) override;

	String name;
	bool running = false;
	int numWorker = 0;
	ActiveThreadMap activeThreads;
	ThreadList inactiveThreads;
	ActionList pendingActions;


};



