#include "LoadingManager.h"
#include <stddef.h>
#include <iostream>
#include "SFXManager.h"




LoadingManager* LoadingManager::sharedInstance = NULL;
LoadingManager* LoadingManager::getInstance()
{
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new LoadingManager();
	}

	return sharedInstance;
}

void LoadingManager::AddAssetTally(int count)
{
	loadMutex.lock();
	maxAssetsCount += count;
	loadMutex.unlock();
}

void LoadingManager::IncrementAssetLoaded()
{
	loadMutex.lock();
	currentAssetsLoaded++;
	std::cout << "Remaining: " << maxAssetsCount - currentAssetsLoaded << std::endl;

	if (maxAssetsCount <= currentAssetsLoaded) {
		status = true;
	}
		

	loadMutex.unlock();
}

void LoadingManager::FinishedLoading()
{
	SFXManager::getInstance()->playStreamMusic();
	//Do Something
}

bool LoadingManager::CheckLoadingStatus()
{
	return status;
}

float LoadingManager::CheckLoadingPercentage()
{
	return (float)currentAssetsLoaded / (float)maxAssetsCount;
}
