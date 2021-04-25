#ifndef PLAYERGUITAB_H
#define PLAYERGUITAB_H

#include "CharacterTab.h"


class PlayerGUITab
{
private:

	//Core
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	sf::Clock keyTimer;
	float keyTimeMax;

	//Character tab
	CharacterTab characterTab;

	//Private functions
	void initKeyTime();

public:

	//Constructor / Destructor
	PlayerGUITab(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerGUITab();

	//Accessors
	const bool getKeyTime();
	const bool isTabOpen();

	void toggleCharacterTab();

	void Update();
	void Render(sf::RenderTarget& target);
};

#endif // !PLAYERGUITAB_H


