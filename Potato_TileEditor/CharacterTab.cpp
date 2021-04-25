#include "stdafx.h"
#include "CharacterTab.h"

void CharacterTab::initText()
{
	//Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(gui::p2fontSize(this->vm, 125));
	this->infoText.setFillColor(sf::Color::White);
	this->infoText.setPosition(
		this->background.getPosition().x + gui::p2pX(2.f, this->vm),
		this->background.getPosition().y + gui::p2pY(2.f, this->vm)
	);

	this->infoText.setString(this->player.toStringCharacterTab());
}

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player)
	: Tab(vm, font, player, false)
{
	//Background
	this->background.setFillColor(sf::Color(10, 10, 10, 255));
	this->background.setSize(sf::Vector2f(gui::p2pX(15.f, this->vm), gui::p2pY(45.f, this->vm)));
	this->background.setPosition(sf::Vector2f(gui::p2pX(3.f, this->vm), gui::p2pY(15.f, this->vm)));

	this->initText();
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::Update()
{
	if (!this->hidden)
	{
		//Update the Character Info
		this->infoText.setString(this->player.toStringCharacterTab());
	}
}

void CharacterTab::Render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(background);
		//target.draw(infoText);
	}
}
