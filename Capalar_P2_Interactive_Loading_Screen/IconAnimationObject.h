#pragma once
#include "AGameObject.h"
class IconAnimationObject: public AGameObject
{
public:
	IconAnimationObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	void incrementNewFrame();
	void adjustFramePosition();

private:
	std::vector<sf::Texture*> textureList;
	float animfps = 0;
	float ticks = 0;
	float speed = 1;

	int frameCount = 0;
	bool state = false;

};

