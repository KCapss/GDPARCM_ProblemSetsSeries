#include "StreamAnimationAssetLoader.h"


#include <fstream>
#include <iostream>
#include <filesystem>
#include <iostream>
#include "IETThread.h"
#include "StringUtils.h"

#include "LoadingManager.h"
#include "TextureManager.h"
#include "IExecutionEvent.h"



StreamAnimationAssetLoader::StreamAnimationAssetLoader(std::string path, std::string animationName, IExecutionEvent* executionEvent) : IWorkerAction()
{
	this->path = path;
	this->execEvent = executionEvent;
	this->assetName = animationName;
	this->durationMultiplier = rand() % 4 + 1;
}

StreamAnimationAssetLoader::~StreamAnimationAssetLoader()
{

}

void StreamAnimationAssetLoader::onStartTask()
{
	//Simulate Large Batch Assets being loaded
	IETThread::sleep(500);

	std::cout << "[Animation Texture] Reading from " << assetName << std::endl;
	path.append("/");


	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		this->durationMultiplier = rand() % 10 + 1;
		IETThread::sleep(150 * durationMultiplier);
		LoadingManager::getInstance()->IncrementAssetLoaded();
		//Concurency Potential Problem
		TextureManager::getInstance()->instantiateAsTexture(entry.path().generic_string() , assetName, true);
	}



	this->execEvent->onFinishedExecution();
	delete this;


}

