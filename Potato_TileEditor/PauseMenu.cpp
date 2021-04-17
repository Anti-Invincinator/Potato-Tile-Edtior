#include "stdafx.h"
#include "PauseMenu.h"

//Constructor/Destructor
PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	: font(font)
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width), 
			static_cast<float>(vm.height))
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init Container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height) - gui::p2pY(14.8f, vm)
		)
	);

	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	this->container.setPosition(
		sf::Vector2f(
			static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
			gui::p2pY(7.4f, vm)
		)
	);

	//Init Text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::p2fontSize(vm, 50));
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + gui::p2pY(4.f, vm)
	);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}


//Functions
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, 
	const float y,
	const float width,
	const float height,
	const std::string text,
	const unsigned font_size)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,																			// posX, posY, sizeX, sizeY
		&this->font, text, font_size,																			// font, text, font size
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),			// idle, hover, pressed Text Color
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)				//idle, hover, pressed Button Color  (0 in alpha to make it a transparent button)
	);
}

void PauseMenu::Update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->Update(mousePosWindow);
	}
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
	target.draw(this->menuText);

	for (auto& i : this->buttons)
	{
		i.second->Render(target);
	}

}