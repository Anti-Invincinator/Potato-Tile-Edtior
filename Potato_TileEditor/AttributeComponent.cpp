#include "stdafx.h"
#include "AttributeComponent.h"

//Constructor / Destructor
AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = 2;

	//Attributes
	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}

//Functions
std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp Next: " << this->expNext << "\n"
		<< "Attribute Points: " << this->attributePoints << "\n";

	return ss.str();
}

void AttributeComponent::loseHP(const int hp)
{
	this->hitpoints -= hp;

	if (this->hitpoints < 0)
		this->hitpoints = 0;
}

void AttributeComponent::loseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

void AttributeComponent::gainHP(const int hp)
{
	this->hitpoints += hp;

	if (this->hitpoints > this->hitpointsMax)
		this->hitpoints = this->hitpointsMax;
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

const bool AttributeComponent::isDead() const
{
	return this->hitpoints <= 0;
}

void AttributeComponent::updateStats(const bool reset)
{
	this->hitpointsMax	= this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->damageMax		= this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->damageMin		= this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->accuracy		= this->dexterity * 5 + this->dexterity / 3 + this->intelligence / 5;
	this->defense		= this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck			= this->intelligence * 2 + this->intelligence / 5;
	
	if (reset)
	{
		this->hitpoints = this->hitpointsMax;
	}
}

void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		++this->attributePoints;
		this->exp -= this->expNext;	
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));	
	}
}

void AttributeComponent::Update()
{
	this->updateLevel();
}