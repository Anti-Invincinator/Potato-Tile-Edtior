#include "stdafx.h"
#include "MeleeWeapon.h"

//CONSTRUCTOR / DESTRUCTOR
MeleeWeapon::MeleeWeapon(unsigned level, unsigned value, std::string texture_file, unsigned damage_min, unsigned damage_max, unsigned range)
	: Weapon(level, value, texture_file, damage_min, damage_max, range)
{
	this->type = ItemTypes::MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::generate(const unsigned level_min, const unsigned level_max)
{
	this->level = rand() % (level_max - level_min + 1) + level_min;

	this->damageMin = this->level * (rand() % 2 + 1);
	this->damageMax = this->level * (rand() % 3 + 1) + this->damageMin; 

	this->range = this->level + rand() % 10 + 50;

	this->value = this->level + this->damageMin + this->damageMax + this->range + (rand() % level * 10);
}
