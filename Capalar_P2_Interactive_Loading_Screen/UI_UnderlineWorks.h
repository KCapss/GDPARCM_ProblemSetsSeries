#pragma once
#include "AGameObject.h"
class UI_UnderlineWorks : public AGameObject
{
public:
	UI_UnderlineWorks(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	bool state = false;
};

