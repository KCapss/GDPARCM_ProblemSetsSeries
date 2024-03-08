#include "StreamAnimationObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "StreamAnimationAssetLoader.h"
#include "JobSystem.h"
#include "LoadingManager.h"
#include "ThreadPool.h";

StreamAnimationObject::StreamAnimationObject(string name) : AGameObject(name)
{
}

void StreamAnimationObject::initialize()
{
	//Retrieve Relative File Path
	String path = TextureManager::getInstance()->RetrieveRelativeAnimationPath(this->name);
	LoadingManager::getInstance()->AddAssetTally(TextureManager::getInstance()->RetrieveSpriteSheetSize(path));


	StreamAnimationAssetLoader* animationLoader = new StreamAnimationAssetLoader(path, name, this);

	ThreadPool* pool = JobSystem::getInstance()->GetThreadPool();
	pool->scheduleTask(animationLoader);
	
}

void StreamAnimationObject::processInput(sf::Event event)
{

}

void StreamAnimationObject::update(sf::Time deltaTime)
{
	if (!doneLoading)
		return;

	ticks += (float)deltaTime.asMilliseconds() * speed;
	if (ticks > 1.0f / animfps && !frameActivated)
	{	
		frameActivated = true;
		ticks = 0;
		frameCount++;
		if (frameCount > textureList.size() - 1) {
			frameCount = 0;

			//std::cout << "Frame Count: " << frameCount << std::endl;
		}
		//incrementNewFrame();
	}
}

void StreamAnimationObject::draw(sf::RenderWindow* targetWindow)
{
	if (this->sprite != nullptr) {
		this->sprite->setPosition(posX, posY);
		targetWindow->draw(*this->sprite);

		if (frameActivated) {
			incrementNewFrame();
			//cout << "frame Count: " << frameCount << endl;
			frameActivated = false;
		}
		
	}
}

void StreamAnimationObject::onFinishedExecution()
{
	spawnObject();
}

void StreamAnimationObject::incrementNewFrame()
{

	this->sprite->setTexture(*textureList[frameCount]);

}

void StreamAnimationObject::spawnObject()
{
	std::cout << "Stream Load as " << this->getName() << "\n";
	animfps = 16 * 0.2f;
	//speed = 0.000025f; //Debatable

	//textureList = TextureManager::getInstance()->RetrieveAnimationTexture(this->name);
	int frameSize = TextureManager::getInstance()->getNumFrames(name);

	for (int i = 0; i < frameSize; i++) {
		textureList.push_back(TextureManager::getInstance()->getFromTextureMap(name, i));
	}


	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, frameCount);
	this->sprite->setTexture(*texture);

	sf::Vector2u spriteSize = texture->getSize();
	this->setScale(0.4f, 0.4f);

	//Debatable
	//this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - sprite->getLocalBounds().width / 2.0f + 250, BaseRunner::WINDOW_HEIGHT / 2.0f - sprite->getLocalBounds().height / 2.0f + 220);
	doneLoading = true;
}

void StreamAnimationObject::adjustFramePosition(sf::Vector2i centerPos)
{
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f + centerPos.x,
		BaseRunner::WINDOW_HEIGHT / 2.0f - centerPos.y);

}

