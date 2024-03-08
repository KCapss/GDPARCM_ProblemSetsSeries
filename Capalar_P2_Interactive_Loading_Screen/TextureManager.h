#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <mutex>

//Threading
class IExecutionEvent;
class ThreadPool;


class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;
	
public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
	void loadStreamingAssets();
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;

	std::vector<sf::Texture*> loadAnimationAnimationTexture(const String assetName);
	std::vector<sf::Texture*> RetrieveAnimationTexture(const String assetAnimName);
	String RetrieveRelativeAnimationPath(String key);
	int RetrieveSpriteSheetSize(String path);

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;

	//Animation Map

	const std::string STREAMING_PATH = "Media/Streaming/";
	int streamingAssetCount = 0;

	void countStreamingAssets();



public:
	void instantiateAsTexture(String path, String assetName, bool isStreaming);

};