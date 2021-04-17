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
	PauseMenu(sf::VideoMode& vm, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,
		const float y, 
		const float width,
		const float height,
		const std::string text,
		const unsigned font_size);
	void Update(const sf::Vector2i& mousePosWindow);
	void Render(sf::RenderTarget& target);
};

#endif // !PAUSEMENU_H