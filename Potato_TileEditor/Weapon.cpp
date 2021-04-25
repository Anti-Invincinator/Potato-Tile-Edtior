#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 50;
	this->damageMin = 1;
	this->damageMax = 2;

	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}


Weapon::Weapon(unsigned level, unsigned value, std::string texture_file)
	:Item(level, value)
{
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR :: PLAYER :: WAS NOT ABLE TO LOAD SWORD WEAPON TEXTURE::" << texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::Weapon(unsigned level, unsigned value, std::string texture_file, unsigned damage_min, unsigned damage_max, unsigned range)
	:Item(level, value)
{
	this->initVariables();

	this->damageMin = damage_min;
	this->damageMax = damage_max;

	//To avoid super high damage in case damage min is greater than damage max
	if (this->damageMin > this->damageMax)
	{
		unsigned temp = this->damageMax;

		this->damageMax = this->damageMin;
		this->damageMin = temp;
	}

	this->range = range;

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR :: PLAYER :: WAS NOT ABLE TO LOAD SWORD WEAPON TEXTURE::" << texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::~Weapon()
{
}

//Accessors
const unsigned& Weapon::getRange() const
{
	return this->range;
}

const unsigned& Weapon::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
	return this->damageMax;
}

const unsigned Weapon::getDamage() const
{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

const bool Weapon::getAttackTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}

	return false;
}
