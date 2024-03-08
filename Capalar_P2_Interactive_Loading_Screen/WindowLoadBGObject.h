#pragma once
#include "AGameObject.h"

class WindowLoadBGObject : public AGameObject
{
public:
	WindowLoadBGObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
private:
	bool state = false;
};

