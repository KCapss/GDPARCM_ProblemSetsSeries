#include "BGScrolling.h"

#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "LoadingManager.h"

BGScrolling::BGScrolling(string name) : AGameObject(name)
{
}

void BGScrolling::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("SpaceStation", 0);
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);


	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	positionPivot = sf::Vector2u(BaseRunner::WINDOW_WIDTH / 2.0f - textureSize.x / 2.0f, BaseRunner::WINDOW_HEIGHT / 2.0f - textureSize.y / 2.0f);
	this->sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x * 2.0f, texture->getSize().y));
	

	//make BG height x k to emulate repeating BG.
	
	//this->setPosition(BaseRunner::WINDOW_WIDTH/2.0f - (textureSize.x * 0.25f)/2.0f, positionPivot.y);
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - (textureSize.x * 1) / 2.0f, positionPivot.y);
	startX = this->sprite->getPosition().x;
}

void BGScrolling::processInput(sf::Event event)
{
}

void BGScrolling::update(sf::Time deltaTime)
{
	if (state)
		return;

	if (LoadingManager::getInstance()->CheckLoadingStatus())
	{
		state = true;
		this->sprite = nullptr;
		return;
	}

	//make BG scroll slowly
	sf::Vector2f position = this->getPosition();
	position.x -= this->SPEED_MULTIPLIER * deltaTime.asSeconds();
	this->setPosition(position.x, position.y);

	sf::Vector2f localPos = this->sprite->getPosition();
	//if (localPos.x < (startX) - (740.0f * 4.0f)) {
	//	//reset position
	//	
	//	this->setPosition(startX, positionPivot.y);
	//}

	if (localPos.x < (startX) - 740.0f) {
		//reset position

		this->setPosition(startX, positionPivot.y);
	}
	else {

	}
}
