#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Gui.h"

class Gui;

class PauseMenu
{
private:
	sf::Font& font;
    sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	//Private Functions
	

public:
	//Constructor/Destructor
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void Update(const sf::Vector2i& mousePosWindow);
	void Render(sf::RenderTarget& target);
};

#endif // !PAUSEMENU_H


