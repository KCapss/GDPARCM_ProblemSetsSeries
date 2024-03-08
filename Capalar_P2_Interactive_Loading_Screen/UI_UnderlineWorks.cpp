#include "UI_UnderlineWorks.h"

#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "SFXManager.h"
#include "LoadingManager.h"

UI_UnderlineWorks::UI_UnderlineWorks(string name) : AGameObject(name)
{
}

void UI_UnderlineWorks::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("UnderBanner", 0);
	this->sprite->setTexture(*texture);

	sf::Vector2u spriteSize = texture->getSize();
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - spriteSize.x / 2.0f, BaseRunner::WINDOW_HEIGHT / 2.0f - spriteSize.y / 2.0f + 100.0f );


}

void UI_UnderlineWorks::processInput(sf::Event event)
{
}

void UI_UnderlineWorks::update(sf::Time deltaTime)
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

