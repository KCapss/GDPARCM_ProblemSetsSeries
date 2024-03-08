#include "UI_LoadingIndicatorObject.h"

#include <iostream>
#include "TextureManager.h"
#include "LoadingManager.h"
#include "BaseRunner.h"

UI_LoadingIndicatorObject::UI_LoadingIndicatorObject(string name) : AGameObject(name)
{
}

void UI_LoadingIndicatorObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//Loading Guidelines
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("loadBar", 0);
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	this->sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x * 9.5f, texture->getSize().y));

	sf::Vector2u spriteSize = sprite->getTexture()->getSize();
	
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - spriteSize.x * 9.5f / 2.0f, BaseRunner::WINDOW_HEIGHT - 100.0f);

	//Actual Load Bar
	this->fillerAssets = new sf::Sprite();
	sf::Texture* textureCopy = TextureManager::getInstance()->getFromTextureMap("LineLoad", 0);
	this->fillerAssets->setTexture(*textureCopy);
	this->fillerAssets->setTextureRect(sf::IntRect(0, 0, texture->getSize().x * 0.5f, textureCopy->getSize().y * 2));

	this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - spriteSize.x * 9.5f / 2.0f, BaseRunner::WINDOW_HEIGHT - 100.0f);
	fillerAssets->setPosition(this->sprite->getPosition().x, BaseRunner::WINDOW_HEIGHT - 100.0f - 1.5f * 2.0f);

}

void UI_LoadingIndicatorObject::processInput(sf::Event event)
{
}

void UI_LoadingIndicatorObject::update(sf::Time deltaTime)
{
	if (isFinished)
		return;

	if (LoadingManager::getInstance()->CheckLoadingStatus()) {
		isFinished = true;
		LoadingManager::getInstance()->FinishedLoading();
	}
	recomputeBarProgression();

}

void UI_LoadingIndicatorObject::draw(sf::RenderWindow* targetWindow)
{
	if (isFinished)
		return;

	AGameObject::draw(targetWindow);

	if(fillerAssets != nullptr)
		targetWindow->draw(*this->fillerAssets);
		
}

void UI_LoadingIndicatorObject::recomputeBarProgression()
{
	barRatio = LoadingManager::getInstance()->CheckLoadingPercentage();
	this->fillerAssets->setTextureRect(sf::IntRect(0, 0, fillerAssets->getTexture()->getSize().x * (max * barRatio), fillerAssets->getTexture()->getSize().y * 2));

}


