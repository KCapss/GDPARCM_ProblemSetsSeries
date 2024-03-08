#include "StreamText.h"
#include "BaseRunner.h"

StreamText::StreamText() : AGameObject("StreamText")
{
}

StreamText::~StreamText()
{
	delete this->shortText->getFont();
	delete this->shortText;
	AGameObject::~AGameObject();
}

void StreamText::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Stream/Font/Din BOLD.ttf");

	this->shortText = new sf::Text();
	this->shortText->setFont(*font);

	this->shortText->setString("GET A CHANCE TO WIN A RUAN MEI CAT");

	this->shortText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->shortText->setOutlineThickness(2.5f);
	this->shortText->setCharacterSize(64);

	float textWidth = shortText->findCharacterPos(shortText->getString().getSize()).x - shortText->findCharacterPos(0).x;
	shortText->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - textWidth / 2.0f + 5, 100);
	

}

void StreamText::processInput(sf::Event event)
{
}

void StreamText::update(sf::Time deltaTime)
{
	
}

void StreamText::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->shortText != nullptr)
		targetWindow->draw(*this->shortText);
}
