#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <mutex>

//Threading
class IExecutionEvent;
class ThreadPool;

class FontManager
{
public:
	typedef std::string String;
	typedef std::vector<std::string> MessageList;
	typedef std::unordered_map<String, MessageList> HashMessageTable;

public:
	static FontManager* getInstance();

	void loadFromLoadingAssetList();
	void loadAssetList(String tag);
	void streamAssetList(String tag, IExecutionEvent* executionEvent);

	MessageList getStreamingTextMap(String key);
	MessageList getTextMap(String key);


	std::vector<sf::Texture*> RetrieveAnimationTexture(const String assetAnimName);

private:
	FontManager();
	FontManager(FontManager const&) {};             // copy constructor is private
	FontManager& operator=(FontManager const&) {};  // assignment operator is private
	static FontManager* sharedInstance;



	HashMessageTable messageMap;
	MessageList baseMessageList;
	MessageList streamMessageList;

	const std::string STREAMING_PATH = "Media/Streaming/";
	//int streamingAssetCount = 0;

	//Threading
	ThreadPool* threadPool;
};

