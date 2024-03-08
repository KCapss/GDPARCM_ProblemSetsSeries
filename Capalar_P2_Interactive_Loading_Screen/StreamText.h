#pragma once
#include "AGameObject.h"
class StreamText: public AGameObject
{
public:
	StreamText();
	~StreamText();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	sf::Text* shortText;
};

