#pragma once
#include "AGameObject.h"

class LoadMainBGObject : public AGameObject
{

public:
	LoadMainBGObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
private:
	float SPEED_MULTIPLIER = 100.0f;
	float shiftInterval = 2.0f;
	float ticks = 0;
	bool state = false;
};

