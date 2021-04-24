#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 20;
	this->damageMin = 1;
	this->damageMax = 2;

	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}


Weapon::Weapon(unsigned value, std::string texture_file)
	:Item(value)
{
	this->initVariables();

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

const bool Weapon::getAttackTimer()
{
	std::cout << this->attackTimer.getElapsedTime().asMilliseconds() << "\n";

	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}

	return false;
}

Item* Weapon::clone()
{
	return nullptr;
}
