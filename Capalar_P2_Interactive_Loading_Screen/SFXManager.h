#pragma once
#include <string>
#include <unordered_map>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "IETThread.h"
class IExecutionEvent;
class ThreadPool;

class SFXManager
{
public:
	typedef std::string String;

	static SFXManager* getInstance();
	
	void loadFromLoadingAssetList();
	void loadAssetList(String tag);
	void streamAssetList(String tag, IExecutionEvent* executionEvent);
	void playLoadMusic();
	void playStreamMusic();

	//Playing Music


	sf::SoundBuffer* getSoundBuffer(std::string key);
	sf::Music* getMusicFile(std::string key);

private:
	// set constructor to private
	SFXManager() {};
	// set copy constructor to private
	SFXManager(SFXManager const&) {}
	// assignment operator is private
	SFXManager& operator=(SFXManager const&) {};
	static SFXManager* sharedInstance;

	void loadSoundBuffer(std::string, std::string);
	void loadMusic(std::string, std::string);
	

	std::unordered_map<std::string, sf::SoundBuffer*> soundBufferMap;
	std::unordered_map<std::string, sf::Music*> musicMap;
	sf::Music* musicTrack;



};

