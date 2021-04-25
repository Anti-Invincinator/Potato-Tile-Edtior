#include "stdafx.h"
#include "Tab.h"

Tab::Tab(sf::VideoMode& vm, sf::Font& font, Player& player, bool hidden)
	: vm(vm), font(font), player(player), hidden(hidden)
{
	
}

Tab::~Tab()
{
}

const bool& Tab::getIsHidden() const
{
	return this->hidden;
}

const bool& Tab::getIsOpen() const
{
	return (this->hidden == false);
}

void Tab::hide()
{
	this->hidden = true;
}

void Tab::show()
{
	this->hidden = false;
}
