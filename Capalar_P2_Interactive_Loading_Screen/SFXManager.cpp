#include <stddef.h>
#include <iostream>
#include "SFXManager.h"


SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance()
{
	//initial only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new SFXManager();
	}

	return sharedInstance;
}


void SFXManager::loadFromLoadingAssetList()
{
	//Load All Music
	loadMusic("loadingMusic", "Media/Loading/Music/LoadingOST.ogg");
	loadMusic("StreamMusic", "Media/Stream/Music/MonodramaOST.ogg");
	
}

void SFXManager::loadAssetList(String tag)
{
}

void SFXManager::streamAssetList(String tag, IExecutionEvent* executionEvent)
{
}

void SFXManager::playLoadMusic()
{
	if (this->musicTrack == nullptr)
		musicTrack = new sf::Music();
	

	if (musicTrack->getStatus() == sf::Music::Stopped) {
		musicTrack = SFXManager::getInstance()->getMusicFile("loadingMusic");
		musicTrack->setVolume(70);
		musicTrack->setLoop(true);
		musicTrack->play();
	}
	
}

void SFXManager::playStreamMusic()
{
	musicTrack->stop();
	musicTrack = SFXManager::getInstance()->getMusicFile("StreamMusic");
	musicTrack->setVolume(20);
	musicTrack->setLoop(true);
	musicTrack->play();
}



sf::SoundBuffer* SFXManager::getSoundBuffer(std::string key)
{
	if (soundBufferMap[key] != NULL) {
		return soundBufferMap[key];
	}

	else {
		std::cout << "No SoundBuffer found for " << key << std::endl;
		return NULL;
	}
}

sf::Music* SFXManager::getMusicFile(std::string key)
{
	if (musicMap[key] != NULL) {
		return musicMap[key];
	}

	else {
		std::cout << "No MusicMap found for " << key << std::endl;
		return NULL;
	}
}

void SFXManager::loadSoundBuffer(std::string key, std::string path)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
	soundBuffer->loadFromFile(path);
	soundBufferMap[key] = soundBuffer;
}

void SFXManager::loadMusic(std::string key, std::string path)
{
	sf::Music* music = new sf::Music();
	if (!music->openFromFile(path)) {
		std::cout << "error loading music for " << path << std::endl;
	}
	
	else {
		musicMap[key] = music;
	}
	
}
