#pragma once
#include "AGameObject.h"
#include "TooltipDialogue.h"

class CaptionDetailHandler : public AGameObject
{
public:
	CaptionDetailHandler();
	~CaptionDetailHandler();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	void SetupStringText();
	void SetupTextFormat();
	void InitializeText();
	void checkInput();

private:
	//Main Title
	sf::Text* titleText;
	
	//Subtitle
	sf::Text* line1Text;
	sf::Text* line2Text;
	sf::Text* line3Text;
	sf::Text* line4Text;

	sf::Text* versionText;
	
	std::vector<sf::Text*> tooltipsList;
	bool state = false;


	//Tooltip
	TooltipDialogue *tooltip;
	float clickDelay = 0.15f;
	float ticks = 0;

	//Input Detection
	bool isPressedFlag = false;
	bool isHold = false;
	bool isClickedTriggered = false;

	
	//Caption Class
	/*
		Consist of..
		1. Title Caption
		2. Description

	*/
	//std::vector<std::string> textList;
	
};

