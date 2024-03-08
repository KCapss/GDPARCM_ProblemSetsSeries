#include "FPSCounter.h"
#include <iostream>
#include "BaseRunner.h"
#include <math.h>
#include <iomanip>
#include <sstream>
#include <string>

FPSCounter::FPSCounter(): AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 175, 0);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(24);
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if(this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{

	//float FPS_estimate = (sf::seconds(1.f / 60.f).asSeconds() / elapsedTime.asSeconds()) * 2.0f;


	float FPS_estimate = 1.0f / elapsedTime.asSeconds();
	float b = floor(FPS_estimate * 100.0f) / 100.0f;

	
	if (FPS_estimate > 60) {
		FPS_estimate = 60.00f;
		
	}

	std::string myval_str;
	{
		std::stringstream ss;
		ss << FPS_estimate;
		myval_str = ss.str();
	}


	string time = "FPS: ";
	//time.append(std::to_string(b));
	time.append(myval_str);
	this->statsText->setString(time);
}