#pragma once
#include "SFML/Graphics.hpp"
#include <mutex>
class LoadingManager
{

public:
	static LoadingManager* getInstance();
	void AddAssetTally(int count);
	void IncrementAssetLoaded();

	void FinishedLoading();

	bool CheckLoadingStatus();
	float CheckLoadingPercentage();


private:
	LoadingManager() {};
	LoadingManager(LoadingManager const&) {};             // copy constructor is private
	LoadingManager& operator=(LoadingManager const&) {};  // assignment operator is private
	static LoadingManager* sharedInstance;


	int maxAssetsCount = 0;
	int currentAssetsLoaded = 0;
	bool status = false;

	std::mutex loadMutex;
};