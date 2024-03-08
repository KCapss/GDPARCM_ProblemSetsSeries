#pragma once
#include <iostream>
#include "IWorkerAction.h"


class IExecutionEvent;
/// <summary>
/// Converted to IWorkerAction  for thread pooling
/// </summary>
class StreamAssetLoader: public IWorkerAction
{
private:
	typedef std::string String;

public:
	StreamAssetLoader(std::string path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask();

	String path;
	IExecutionEvent* execEvent;
};

