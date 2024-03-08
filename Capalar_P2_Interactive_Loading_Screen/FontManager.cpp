#include"FontManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>

#include "FontManager.h"
#include "StringUtils.h"

//Multithreadings
#include "IETThread.h"
#include "StreamAssetLoader.h"
#include "IExecutionEvent.h"

//Threading
#include "ThreadPool.h"

//a singleton class
FontManager* FontManager::sharedInstance = NULL;

FontManager* FontManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new FontManager();
		//sharedInstance->threadPool = new ThreadPool ("TextureWorker", 16);
	}

	return sharedInstance;
}

void FontManager::loadFromLoadingAssetList()
{
	std::cout << "[FontManager] Reading from asset list" << std::endl;
	std::ifstream streamMain("Media/Loading/Title.txt");
	String path;

	MessageList titleMap;
	
	while (std::getline(streamMain, path))
	{
		titleMap.push_back(path);
	}

	MessageList captionMap;
	std::ifstream streamSub("Media/Loading/FlavorText.txt");

	while (std::getline(streamSub, path))
	{
		captionMap.push_back(path);
	}

	
	messageMap.insert(std::pair("Title", titleMap));
	messageMap.insert(std::pair("FlavorText", captionMap));

}

void FontManager::loadAssetList(String tag)
{
}

void FontManager::streamAssetList(String tag, IExecutionEvent* executionEvent)
{

}

FontManager::MessageList FontManager::getStreamingTextMap(String key)
{
	MessageList list;

	for (auto i = messageMap.begin(); i != messageMap.end(); i++) {
		if (i->first == key) {
			list = i->second;
		}
	}
	
	return list;
}

FontManager::MessageList FontManager::getTextMap(String key)
{
	MessageList list;

	for (auto i = messageMap.begin(); i != messageMap.end(); i++) {
		if (i->first == key) {
			list = i->second;
		}
	}

	return list;
}

FontManager::FontManager()
{
	//this->countStreamingAssets();

	////Threading
	//this->threadPool = new ThreadPool("TextureWorker", 32);
}
//
//void FontManager::loadFromAssetList()
//{
//	std::cout << "[TextureManager] Reading from asset list" << std::endl;
//	std::ifstream stream("Media/assets.txt");
//	String path;
//
//	while (std::getline(stream, path))
//	{
//		std::vector<String> tokens = StringUtils::split(path, '/');
//		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
//		//this->instantiateAsTexture(path, assetName, false);
//		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
//	}
//
//	this->threadPool->startScheduler();
//}
//
//std::vector<sf::Texture*> FontManager::RetrieveAnimationTexture(const String assetAnimName) {
//	std::vector<sf::Texture*> animListName;
//
//	std::cout << "[TextureManager] Reading from asset list" << std::endl;
//	String mainPath = "Media/";
//	mainPath.append(assetAnimName);
//	mainPath.append(".txt");
//
//	std::ifstream stream(mainPath);
//	String path;
//	std::cout << "[TextureManager] Loaded anim texture: " << assetAnimName << std::endl;
//
//	while (std::getline(stream, path))
//	{
//		sf::Texture* texture = new sf::Texture();
//		texture->loadFromFile(path);
//		animListName.push_back(texture);
//	}
//
//	if (animListName.size() > 0)
//		return animListName;
//
//	else
//	{
//		std::cout << "Missing Anim Texture" << std::endl;
//		return animListName;
//	}
//
//}
//
//void FontManager::loadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
//{
//	int fileNum = 0;
//
//	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
//		if (index == fileNum)
//		{
//			//simulate loading of very large file
//			//<code here for thread sleeping. Fill this up only when instructor told so.>
//
//
//			//<code here for loading asset>
//
//			//With StreamingAssets
//			std::string path = entry.path().generic_string();
//			StreamAssetLoader* assetloader = new StreamAssetLoader(path, executionEvent);
//			this->threadPool->scheduleTask(assetloader);
//
//
//			////Before Streaming Assets
//			//String path = entry.path().generic_string();
//			//std::vector<String> tokens = StringUtils::split(path, '/');
//			//String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
//			//this->instantiateAsTexture(path, assetName, true);
//
//			break;
//		}
//
//		fileNum++;
//	}
//}
//
//void FontManager::loadStreamingAssets()
//{
//	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
//		String path = entry.path().generic_string();
//		std::vector<String> tokens = StringUtils::split(path, '/');
//		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
//		//this->instantiateAsTexture(path, assetName, true);
//		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
//	}
//}
//
//sf::Texture* FontManager::getFromTextureMap(const String assetName, int frameIndex)
//{
//	if (!this->textureMap[assetName].empty()) {
//		return this->textureMap[assetName][frameIndex];
//	}
//	else {
//		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
//		return NULL;
//	}
//}
//
//int FontManager::getNumFrames(const String assetName)
//{
//	if (!this->textureMap[assetName].empty()) {
//		return this->textureMap[assetName].size();
//	}
//	else {
//		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
//		return 0;
//	}
//}
//
//sf::Texture* FontManager::getStreamTextureFromList(const int index)
//{
//	return this->streamTextureList[index];
//}
//
//int FontManager::getNumLoadedStreamTextures() const
//{
//	return  this->streamTextureList.size();
//}
//
//void FontManager::countStreamingAssets()
//{
//
//	this->streamingAssetCount = 0;
//	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
//		this->streamingAssetCount++;
//	}
//	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
//}



