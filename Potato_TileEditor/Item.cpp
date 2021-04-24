#include "stdafx.h"
#include "Item.h"

void Item::initVariables()
{

}

//CONSTRUCTOR / DESTRUCTOR
Item::Item(unsigned value)
{
	this->initVariables();

	this->value = value;
	this->type = ItemTypes::DEFAULT_ITEM;
}

Item::~Item()
{
}
