#pragma once
#include <iostream>
//Threading
class IExecutionEvent;
class ThreadPool;

class JobSystem
{
public:
	typedef std::string String;
	
public:
	static JobSystem* getInstance();
	void initializeJob();
	ThreadPool* GetThreadPool();


private:
	JobSystem();
	JobSystem(JobSystem const&) {};             // copy constructor is private
	JobSystem& operator=(JobSystem const&) {};  // assignment operator is private

	static JobSystem* sharedInstance;
	int processor_count;
	ThreadPool* threadPool;

};

