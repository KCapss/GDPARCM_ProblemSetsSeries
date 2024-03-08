#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"
#include "StringUtils.h"
#include "IETThread.h"
#include "StreamAssetLoader.h"
#include "IExecutionEvent.h"
#include "JobSystem.h"

//Threading
#include "ThreadPool.h"

//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new TextureManager();
		//sharedInstance->threadPool = new ThreadPool ("TextureWorker", 16);
	}

	return sharedInstance;
}

TextureManager::TextureManager()
{
	this->countStreamingAssets();
	
	////Threading
	//this->threadPool = new ThreadPool("TextureWorker", 32);
	

}

void TextureManager::loadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/Loading/assets.txt");
	String path;

	while(std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}

	//this->threadPool->startScheduler();
}




std::vector<sf::Texture*> TextureManager::loadAnimationAnimationTexture(const String assetName)
{
	std::ifstream stream("Media/Stream/.txt");
	return std::vector<sf::Texture*>();
}

//Need to replace/add for loading only
std::vector<sf::Texture*> TextureManager::RetrieveAnimationTexture(const String assetAnimName) {
	std::vector<sf::Texture*> animListName;

	//std::cout << "[TextureManager] Reading from asset list" << std::endl;
	String mainPath = "Media/Loading/";
	mainPath.append(assetAnimName);
	mainPath.append(".txt");

	std::ifstream stream(mainPath);
	String path;
	std::cout << "[TextureManager] Loaded anim texture: " << assetAnimName << std::endl;

	while (std::getline(stream, path))
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(path);
		animListName.push_back(texture);
	}

	if (animListName.size() > 0)
		return animListName;

	else
	{
		std::cout << "Missing Anim Texture" << std::endl;
		return animListName;
	}

}

TextureManager::String TextureManager::RetrieveRelativeAnimationPath(String key)
{
	String path = "";
	String animationPath = "Media/Stream/AnimationFrames";
	for (const auto& entry : std::filesystem::directory_iterator(animationPath)) {

		std::vector<String> tokens = StringUtils::split(entry.path().generic_string(), '/');
		String assetName = tokens[tokens.size()-1];

		
		if (key == assetName) {
			path = entry.path().generic_string();
			break;
		}
			

	}
	
	return path;
}

int TextureManager::RetrieveSpriteSheetSize(String path)
{
	int count = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {

		count++;

	}

	return count;
}

void TextureManager::loadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;
	
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if(index == fileNum)
		{
			//simulate loading of very large file
			//<code here for thread sleeping. Fill this up only when instructor told so.>
			
			
			//<code here for loading asset>

			//With StreamingAssets
			std::string path = entry.path().generic_string();
			StreamAssetLoader* assetloader = new StreamAssetLoader(path, executionEvent);
			//this->threadPool->scheduleTask(assetloader);


			////Before Streaming Assets
			//String path = entry.path().generic_string();
			//std::vector<String> tokens = StringUtils::split(path, '/');
			//String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
			//this->instantiateAsTexture(path, assetName, true);
			
			break;
		}

		fileNum++;
	}
}

void TextureManager::loadStreamingAssets()
{
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		String path = entry.path().generic_string();
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, true);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getStreamTextureFromList(const int index)
{
	return this->streamTextureList[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return  this->streamTextureList.size();
}

void TextureManager::countStreamingAssets()
{

	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void TextureManager::instantiateAsTexture(String path, String assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->textureMap[assetName].push_back(texture);

	if(isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}
	
}
