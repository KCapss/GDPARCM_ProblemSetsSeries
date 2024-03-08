#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"

class StreamBGObject : public AGameObject, public IExecutionEvent
{

public:
	StreamBGObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void onFinishedExecution();

private:
	void spawnObject();

};

