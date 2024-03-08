#pragma once
#include "AGameObject.h"

class BGScrolling: public AGameObject
{
public:
	BGScrolling(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
private:
	const float SPEED_MULTIPLIER = 500.0f;
	const float pixelSize = 720.0f;
	float startX;

	bool state = false;
	sf::Vector2u positionPivot;

};

