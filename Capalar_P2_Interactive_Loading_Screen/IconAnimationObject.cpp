#include "IconAnimationObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "LoadingManager.h"

IconAnimationObject::IconAnimationObject(string name) : AGameObject(name)
{
}

void IconAnimationObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";
	animfps = 16;
	speed = 0.000025f;

	textureList = TextureManager::getInstance()->RetrieveAnimationTexture(this->name);

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = textureList[0];
	this->sprite->setTexture(*texture);

	sf::Vector2u spriteSize = texture->getSize();
	this->setScale(0.20f, 0.20f);
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - sprite->getLocalBounds().width / 2.0f + 250, BaseRunner::WINDOW_HEIGHT / 2.0f - sprite->getLocalBounds().height / 2.0f + 220);
	


}

void IconAnimationObject::processInput(sf::Event event)
{
}

void IconAnimationObject::update(sf::Time deltaTime)
{
	if (state)
		return;

	if (LoadingManager::getInstance()->CheckLoadingStatus())
	{
		state = true;
		this->sprite = nullptr;
		return;
	}

	ticks += (float)deltaTime.asMilliseconds() * 1000.0f * speed;
	if (ticks > 1.0f / animfps)
	{
		ticks = 0;
		frameCount++;
		if (frameCount > textureList.size() - 1) {
			frameCount = 0;
			
			//std::cout << "Frame Count: " << frameCount << std::endl;
		}
		incrementNewFrame();
	}
}

void IconAnimationObject::incrementNewFrame()
{
	sf::Texture* texture = textureList[frameCount];
	this->sprite->setTexture(*texture);

	adjustFramePosition();
}

void IconAnimationObject::adjustFramePosition()
{
	
}


