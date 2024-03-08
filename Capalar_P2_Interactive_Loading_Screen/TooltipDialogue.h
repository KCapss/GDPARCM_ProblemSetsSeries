#pragma once
#include "SFML/Graphics/Text.hpp"
#include <iostream>
#include <vector>

class TooltipDialogue
{
public:
	TooltipDialogue();
	void initialize();

	void NextDialogue();
	void RetrieveNextLine(std::vector<sf::Text*> body);
	void RecomputeMiddleLine(sf::Text* text, int index);


private:
	std::vector<std::string> titleHolder;
	std::vector<std::string> flavorText;

	//Overflow Resolution
	float ratioFill = 1;
	float warningLine = 1;
	float maxBorder;

	float titleHeight = 300;
	float titleSpacing = 50;
	float flavorTextSpacing = 30;

	int dialogueIndex = 0;
	int dialogueMaxSize = 0;
};

