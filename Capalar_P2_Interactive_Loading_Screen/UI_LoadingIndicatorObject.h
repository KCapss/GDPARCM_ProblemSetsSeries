#pragma once
#include "AGameObject.h"
class UI_LoadingIndicatorObject: public AGameObject
{
public:
	UI_LoadingIndicatorObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow) override;

	void recomputeBarProgression();

private:
	sf::Sprite* fillerAssets;
	//Tracker
	float min = 0;
	float max = 9.5f;

	float barRatio;
	bool isFinished = false;

	//Loading Tracker
	float scoreCount;
	float maxCount;

};

