#include "stdafx.h"
#include "Item.h"

void Item::initVariables()
{

}

//CONSTRUCTOR / DESTRUCTOR
Item::Item(unsigned level, unsigned value)
{
	this->initVariables();

	this->level = level;
	this->value = value;
	this->type = ItemTypes::DEFAULT_ITEM;
}

Item::~Item()
{
}
