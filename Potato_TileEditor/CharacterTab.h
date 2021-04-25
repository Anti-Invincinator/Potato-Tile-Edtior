#ifndef CHARACTERTAB_H
#define CHARACTERTAB_H

#include "Tab.h"

class CharacterTab 
	:public Tab
{
private:
	sf::RectangleShape background;
	sf::Text infoText;

	void initText();

public:
	CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~CharacterTab();

	void Update();
	void Render(sf::RenderTarget& target);
};

#endif // !CHARACTERTAB_H


