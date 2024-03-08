#include "LoadMainBGObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "LoadingManager.h"

LoadMainBGObject::LoadMainBGObject(string name) : AGameObject(name)
{
}

void LoadMainBGObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Galaxy", 0);
	this->sprite->setTexture(*texture);

	
	this->setPosition(0, 0);

	ticks = shiftInterval / 2.0f;
}

void LoadMainBGObject::processInput(sf::Event event)
{
}

void LoadMainBGObject::update(sf::Time deltaTime)
{
	if (state)
		return;

	if (LoadingManager::getInstance()->CheckLoadingStatus())
	{
		state = true;
		this->sprite = nullptr;
		return;
	}
	
	
}

