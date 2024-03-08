#pragma once
#include <iostream>
#include "IWorkerAction.h"



class IExecutionEvent;
class StreamAnimationAssetLoader : public IWorkerAction
{
private:
	typedef std::string String;

public:
	StreamAnimationAssetLoader(std::string path, std::string animationName, IExecutionEvent* executionEvent);
	~StreamAnimationAssetLoader();

private:
	void onStartTask();

	float durationMultiplier;

	String path;
	String assetName;
	IExecutionEvent* execEvent;
};

