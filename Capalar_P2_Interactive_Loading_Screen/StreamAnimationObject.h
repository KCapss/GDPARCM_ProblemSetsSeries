#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
class StreamAnimationObject: public AGameObject, public IExecutionEvent
{

public:
	StreamAnimationObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow) override;
	void onFinishedExecution();
	void adjustFramePosition(sf::Vector2i centerPos);

private:
	void incrementNewFrame();
	void spawnObject();
	

private:
	std::vector<sf::Texture*> textureList;
	float animfps = 0;
	float ticks = 0;
	float speed = 1;


	bool frameActivated = false;
	int frameCount = 0;
	bool doneLoading = false;

};

