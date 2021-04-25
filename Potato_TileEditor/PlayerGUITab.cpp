#include "stdafx.h"
#include "PlayerGUITab.h"


void PlayerGUITab::initKeyTime()
{
	this->keyTimeMax = 500.f;
	this->keyTimer.restart();
}

//Constructor / Destructor
PlayerGUITab::PlayerGUITab(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player),
	characterTab(vm, font, player)
{
	this->initKeyTime();
}

PlayerGUITab::~PlayerGUITab()
{
}

const bool PlayerGUITab::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asMilliseconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}

const bool PlayerGUITab::isTabOpen()
{
	return this->characterTab.getIsOpen();
}

void PlayerGUITab::toggleCharacterTab()
{
	if (this->characterTab.getIsHidden())
		this->characterTab.show();

	else
		this->characterTab.hide();
}

void PlayerGUITab::Update()
{
	this->characterTab.Update();
}

void PlayerGUITab::Render(sf::RenderTarget& target)
{
	this->characterTab.Render(target);
}

