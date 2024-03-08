#pragma once
#include "AGameObject.h"
class FPSCounter :    public AGameObject
{
	public:
		FPSCounter();
		~FPSCounter();
		void initialize() override;
		void processInput(sf::Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderWindow* targetWindow) override;
	
	private:
		sf::Time updateTime;
		sf::Text* statsText;
		int framesPassed = 0;

		//Add on
		sf::Clock clock;
		sf::Clock fpsClock;

		sf::Time time;
		sf::Time timer;

		void updateFPS(sf::Time elapsedTime);
		
};

