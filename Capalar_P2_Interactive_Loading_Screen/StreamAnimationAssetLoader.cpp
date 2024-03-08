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
	std::cout << "[Animation Texture] Reading from " << assetName << std::endl;
	path.append("/");


	for (const auto& entry : std::filesystem::directory_iterator(path)) {

		//Simulate the randomness of the size of a single frame
		this->durationMultiplier = rand() % 10 + 1;
		IETThread::sleep(250 * durationMultiplier);

		LoadingManager::getInstance()->IncrementAssetLoaded(); //Add to the progression Meter
		//Concurency Potential Problem
		TextureManager::getInstance()->instantiateAsTexture(entry.path().generic_string() , assetName, true);
	}



	this->execEvent->onFinishedExecution();
	delete this;


}

