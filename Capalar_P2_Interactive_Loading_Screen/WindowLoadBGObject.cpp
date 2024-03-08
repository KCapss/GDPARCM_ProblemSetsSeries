#include "WindowLoadBGObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "LoadingManager.h"

WindowLoadBGObject::WindowLoadBGObject(string name) : AGameObject(name)
{
}

void WindowLoadBGObject::initialize()
{
	
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("OpenWindow", 0);
	this->sprite->setTexture(*texture);

	sf::Vector2u spriteSize = texture->getSize();
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - spriteSize.x/2.0f, BaseRunner::WINDOW_HEIGHT / 2.0f - spriteSize.y/2.0f);

	
}

void WindowLoadBGObject::processInput(sf::Event event)
{
}

void WindowLoadBGObject::update(sf::Time deltaTime)
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

