#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "JobSystem.h"

//Music
#include "SFXManager.h"

//BG
#include "BGObject.h"
#include "LoadMainBGObject.h"
#include "WindowLoadBGObject.h"
#include "BGScrolling.h"

//Animation
#include "IconAnimationObject.h"

//UI 
#include "UI_UnderlineWorks.h"
#include "UI_LoadingIndicatorObject.h"

#include "TextureManager.h"
#include "FontManager.h"

//Text
#include "FPSCounter.h"
#include "CaptionDetailHandler.h"

//Streaming
#include "StreamAnimationObject.h"
#include "StreamBGObject.h"
#include "StreamText.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "P2 - Capalar, Loading Screen ", sf::Style::Close) {

	//=====load loading screen texture
	JobSystem::getInstance()->initializeJob();
	TextureManager::getInstance()->loadFromAssetList();
	FontManager::getInstance()->loadFromLoadingAssetList();
	SFXManager::getInstance()->loadFromLoadingAssetList();
	
	//Streaming Assets
	StreamBGObject* streamBG = new StreamBGObject("StreamBG");
	GameObjectManager::getInstance()->addObject(streamBG);
	

	//Sprite Sheet
	StreamAnimationObject* bladeIcon = new StreamAnimationObject("Blade");
	GameObjectManager::getInstance()->addObject(bladeIcon);
	bladeIcon->adjustFramePosition(sf::Vector2i(-950,-200));

	StreamAnimationObject* blade1Icon = new StreamAnimationObject("Blade");
	GameObjectManager::getInstance()->addObject(blade1Icon);
	blade1Icon->adjustFramePosition(sf::Vector2i(-950, 50));

	StreamAnimationObject* blade2Icon = new StreamAnimationObject("Blade");
	GameObjectManager::getInstance()->addObject(blade2Icon);
	blade2Icon->adjustFramePosition(sf::Vector2i(-950, 300));

	StreamAnimationObject* guinaifenIcon = new StreamAnimationObject("Guinaifen");
	GameObjectManager::getInstance()->addObject(guinaifenIcon);
	guinaifenIcon->adjustFramePosition(sf::Vector2i(-650, -250));

	StreamAnimationObject* guinaifen1Icon = new StreamAnimationObject("Guinaifen");
	GameObjectManager::getInstance()->addObject(guinaifen1Icon);
	guinaifen1Icon->adjustFramePosition(sf::Vector2i(-650, -100));

	StreamAnimationObject* guinaifen2Icon = new StreamAnimationObject("Guinaifen");
	GameObjectManager::getInstance()->addObject(guinaifen2Icon);
	guinaifen2Icon->adjustFramePosition(sf::Vector2i(-650, 150));

	StreamAnimationObject* claraIcon = new StreamAnimationObject("Clara");
	GameObjectManager::getInstance()->addObject(claraIcon);
	claraIcon->adjustFramePosition(sf::Vector2i(-350, -275));

	StreamAnimationObject* dangHengIcon = new StreamAnimationObject("Dang Heng");
	GameObjectManager::getInstance()->addObject(dangHengIcon);
	dangHengIcon->adjustFramePosition(sf::Vector2i(50, -275));

	StreamAnimationObject* hertaIcon = new StreamAnimationObject("Herta");
	GameObjectManager::getInstance()->addObject(hertaIcon);
	hertaIcon->adjustFramePosition(sf::Vector2i(350, -250));

	StreamAnimationObject* herta1Icon = new StreamAnimationObject("Herta");
	GameObjectManager::getInstance()->addObject(herta1Icon);
	herta1Icon->adjustFramePosition(sf::Vector2i(350, -100));

	StreamAnimationObject* herta2Icon = new StreamAnimationObject("Herta");
	GameObjectManager::getInstance()->addObject(herta2Icon);
	herta2Icon->adjustFramePosition(sf::Vector2i(350, 150));


	StreamAnimationObject* marchIcon = new StreamAnimationObject("March");
	GameObjectManager::getInstance()->addObject(marchIcon);
	marchIcon->adjustFramePosition(sf::Vector2i(650, -200));

	StreamAnimationObject* march1Icon = new StreamAnimationObject("March");
	GameObjectManager::getInstance()->addObject(march1Icon);
	march1Icon->adjustFramePosition(sf::Vector2i(650, 50));

	StreamAnimationObject* march2Icon = new StreamAnimationObject("March");
	GameObjectManager::getInstance()->addObject(march2Icon);
	march2Icon->adjustFramePosition(sf::Vector2i(650, 300));

	StreamText* streamText = new StreamText();
	GameObjectManager::getInstance()->addObject(streamText);
	



	//===== Loading  Screen Assets
	BGScrolling* scrollingBG = new BGScrolling("ScrollingBg");
	GameObjectManager::getInstance()->addObject(scrollingBG);

	//Animation
	IconAnimationObject* kafkaIcon = new IconAnimationObject("Kafka");
	GameObjectManager::getInstance()->addObject(kafkaIcon);


	LoadMainBGObject* loadBgObject = new LoadMainBGObject("MainBGObject");
	GameObjectManager::getInstance()->addObject(loadBgObject);
	WindowLoadBGObject* windowBGObject = new WindowLoadBGObject("WindowObject");
	GameObjectManager::getInstance()->addObject(windowBGObject);

	//UI
	UI_LoadingIndicatorObject* loadBar = new UI_LoadingIndicatorObject("LoadingBar");
	GameObjectManager::getInstance()->addObject(loadBar);
	UI_UnderlineWorks* underline = new UI_UnderlineWorks("Underline");
	GameObjectManager::getInstance()->addObject(underline);
	

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
	CaptionDetailHandler *captions = new CaptionDetailHandler();
	GameObjectManager::getInstance()->addObject(captions);

	//SFX
	SFXManager::getInstance()->playLoadMusic();
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			//update(TIME_PER_FRAME);
			update(elapsedTime);
		}
		
		render();
	}
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}