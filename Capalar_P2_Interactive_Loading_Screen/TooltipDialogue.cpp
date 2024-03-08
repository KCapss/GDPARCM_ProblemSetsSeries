#include "TooltipDialogue.h"
#include "FontManager.h"
#include <sstream>
#include "BaseRunner.h"


TooltipDialogue::TooltipDialogue()
{
	titleHolder = FontManager::getInstance()->getTextMap("Title");
	flavorText = FontManager::getInstance()->getTextMap("FlavorText");
}

void TooltipDialogue::initialize()
{
	//Determine the max size of the tooltips
	dialogueMaxSize = titleHolder.size();

	//Determine Borders
	ratioFill = 0.9f;
	warningLine = ratioFill - 0.1f;
	maxBorder = BaseRunner::WINDOW_WIDTH * ratioFill;
}

void TooltipDialogue::NextDialogue()
{
	this->dialogueIndex++;

	if (dialogueIndex > dialogueMaxSize - 1) {
		dialogueIndex = 0;
	}
}

void TooltipDialogue::RetrieveNextLine(std::vector<sf::Text*> body)
{
	if (dialogueMaxSize == 0)
		return;


	int lineVal = 1;
	float screenWidth = BaseRunner::WINDOW_WIDTH;
	std::vector<sf::Text*> textList;

	//Retrieve the main text;
	body[0]->setString(titleHolder[dialogueIndex]);

	//Retrieve Body Text;
	std::string baseSentence;
	std::string finalLineSentence;


	//string s = "Somewhere down the road";
	string copy = flavorText[dialogueIndex];

	istringstream iss(flavorText[dialogueIndex]);

	do {
		string subs;
		iss >> subs;
		subs.append(" ");

		baseSentence.append(subs);
		//Compute the new value of the new line
		body[lineVal]->setString(baseSentence);

		float widthBody = body[lineVal]->findCharacterPos(baseSentence.length()).x - body[lineVal]->findCharacterPos(0).x;
		if (widthBody > maxBorder || widthBody > screenWidth * warningLine) {
			//Create a new line from that
			body[lineVal]->setString(finalLineSentence);
			lineVal++;

			baseSentence = "";
			finalLineSentence = "";
		}
		
		else {
			finalLineSentence = baseSentence;
		}


	} while (iss);

	body[lineVal]->setString(finalLineSentence);

	for (int i = lineVal + 1; i < body.size(); i++) {
		body[i]->setString("");
	}

	for (int i = 0; i < body.size(); i++) {
		if (body[i]->getString().getSize() > 0)
			RecomputeMiddleLine(body[i], i);
	}

	//Do computation to all lines
}

void TooltipDialogue::RecomputeMiddleLine(sf::Text* text, int index)
{
	float textWidth = text->findCharacterPos(text->getString().getSize()).x - text->findCharacterPos(0).x;
	float height = BaseRunner::WINDOW_HEIGHT;
	if(index == 0)//title
	//Attempt to center and apply offset
	text->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - textWidth / 2.0f + 5, height - titleHeight);

	else
	{
		text->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f - textWidth / 2.0f + 5,
			height - (titleHeight - titleSpacing - ((index - 1) * flavorTextSpacing)));
	}
	
}
