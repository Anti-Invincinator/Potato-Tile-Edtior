#ifndef TAB_H
#define TAB_H

#include "Player.h"
#include "Gui.h"


class Tab
{
protected:
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;
	bool hidden;

public:
	Tab(sf::VideoMode& vm, sf::Font& font, Player& player, bool hidden);
	virtual ~Tab();

	//Accessors
	const bool& getIsHidden() const;
	const bool& getIsOpen() const;


	//Modifiers
	void hide();
	void show();

	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
};



#endif // !TAB_H
