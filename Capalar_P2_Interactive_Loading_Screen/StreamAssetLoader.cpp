#include "StreamAssetLoader.h"
#include <iostream>
#include "IETThread.h"
#include "StringUtils.h"
#include "TextureManager.h"
#include "IExecutionEvent.h"
#include "LoadingManager.h"


StreamAssetLoader::StreamAssetLoader(std::string path, IExecutionEvent* executionEvent) : IWorkerAction()
{
	this->path = path;
	this->execEvent = executionEvent;

	
}

StreamAssetLoader::~StreamAssetLoader()
{
}

void StreamAssetLoader::onStartTask()
{
	//std::cout << "Working Threads" << std::endl;
	IETThread::sleep(1000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	this->execEvent->onFinishedExecution();

	LoadingManager::getInstance()->IncrementAssetLoaded();

	delete this;


}
