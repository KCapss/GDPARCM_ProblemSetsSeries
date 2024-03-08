#include "CaptionDetailHandler.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"
#include "LoadingManager.h"

CaptionDetailHandler::CaptionDetailHandler() : AGameObject("FPSCounter")
{
}

CaptionDetailHandler::~CaptionDetailHandler()
{
	delete this->line1Text->getFont();
	delete this->line1Text;
	AGameObject::~AGameObject();
}

void CaptionDetailHandler::initialize()
{
	/*sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(175, 0);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);*/

	tooltip = new TooltipDialogue();
	tooltip->initialize();

	this->sprite = new sf::Sprite();

	SetupTextFormat();
	SetupStringText();
	InitializeText();
	
}

void CaptionDetailHandler::processInput(sf::Event event)
{
	bool boolState = isHold;

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (!isPressedFlag) {
			isHold = true;
		}
		//cout << "Press" << endl;
		break;

	case sf::Event::MouseButtonReleased:
		isHold = false;
		//cout << "Release" << endl;
		break;
	}

	if (boolState != isHold) {
		isPressedFlag = !isPressedFlag;
	}

}

void CaptionDetailHandler::update(sf::Time deltaTime)
{
	ticks += deltaTime.asSeconds();
	if (ticks > clickDelay) {
		ticks = 0;
		isClickedTriggered = false;
	}

	checkInput();
}

void CaptionDetailHandler::draw(sf::RenderWindow* targetWindow)
{
	if (state)
		return;

	if (LoadingManager::getInstance()->CheckLoadingStatus())
	{
		state = true;
		this->sprite = nullptr;
		return;
	}
	AGameObject::draw(targetWindow);
	
	if (this->titleText != nullptr)
		targetWindow->draw(*this->titleText);

	if (this->versionText != nullptr)
		targetWindow->draw(*this->versionText);


	if (this->line1Text != nullptr)
		targetWindow->draw(*this->line1Text);

	if (this->line2Text != nullptr)
		targetWindow->draw(*this->line2Text);
}

void CaptionDetailHandler::SetupStringText()
{


	//Attempt to center and apply offset
	this->titleText->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f , BaseRunner::WINDOW_HEIGHT - 250);
	this->line1Text->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f , BaseRunner::WINDOW_HEIGHT - 200);
	this->line2Text->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f, BaseRunner::WINDOW_HEIGHT - 150);
	this->versionText->setPosition(30, BaseRunner::WINDOW_HEIGHT - 40);

	//Debugging Checking of size
}

void CaptionDetailHandler::SetupTextFormat()
{
	sf::Font* fontMain = new sf::Font();
	fontMain->loadFromFile("Media/Loading/Font/DIN Bold.ttf");

	this->titleText = new sf::Text();
	this->titleText->setFont(*fontMain);
	this->titleText->setFillColor(sf::Color(214, 196, 158));
	this->titleText->setOutlineThickness(1);
	this->titleText->setCharacterSize(36);


	sf::Font* fontBody = new sf::Font();
	fontBody->loadFromFile("Media/Loading/Font/DIN.ttf");

	this->line1Text = new sf::Text();
	this->line1Text->setFont(*fontBody);
	this->line1Text->setFillColor(sf::Color(214, 196, 158));
	this->line1Text->setOutlineThickness(1);
	this->line1Text->setCharacterSize(24);

	this->line2Text = new sf::Text();
	this->line2Text->setFont(*fontBody);
	this->line2Text->setFillColor(sf::Color(214, 196, 158));
	this->line2Text->setOutlineThickness(1);
	this->line2Text->setCharacterSize(24);


	//Version Information
	sf::Font* versionFont = new sf::Font();
	versionFont->loadFromFile("Media/Loading/Font/DIN Bold.ttf");

	this->versionText = new sf::Text();
	this->versionText->setFont(*fontBody);
	this->versionText->setFillColor(sf::Color(150, 150, 150, 150));
	this->versionText->setOutlineThickness(2);
	this->versionText->setCharacterSize(24);

	versionText->setString("GDPARCM: This is an imitation");


	//Push All of them into a single vector
	tooltipsList.push_back(titleText);
	tooltipsList.push_back(line1Text);
	tooltipsList.push_back(line2Text);


}

void CaptionDetailHandler::InitializeText()
{
	tooltip->RetrieveNextLine(tooltipsList);
	int i = 0;
}

void CaptionDetailHandler::checkInput()
{
	if (isPressedFlag && !isClickedTriggered)
	{
		isClickedTriggered = true;
		
		//Do Something to transition
		tooltip->NextDialogue();
		tooltip->RetrieveNextLine(tooltipsList);
		isPressedFlag = false;
	}
}


