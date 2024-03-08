#include "StreamBGObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

#include "StreamAssetLoader.h"
#include "JobSystem.h"
#include "ThreadPool.h";
#include "LoadingManager.h"

StreamBGObject::StreamBGObject(string name) : AGameObject(name)
{
	//Initialize Assets
}

void StreamBGObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	StreamAssetLoader* bgAssetsload = new StreamAssetLoader("Media/Stream/Texture/" + name + ".png", this);
	ThreadPool* copyPool = JobSystem::getInstance()->GetThreadPool();
	copyPool->scheduleTask(bgAssetsload);
	LoadingManager::getInstance()->AddAssetTally(1);
}

void StreamBGObject::processInput(sf::Event event)
{
}

void StreamBGObject::update(sf::Time deltaTime)
{


}

void StreamBGObject::onFinishedExecution()
{
	cout << "FinishedLoadingBG" << endl;
	spawnObject();
}

void StreamBGObject::spawnObject()
{
	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("StreamBG", 0);
	this->sprite->setTexture(*texture);
}
