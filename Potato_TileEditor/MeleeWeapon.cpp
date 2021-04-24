#include "stdafx.h"
#include "MeleeWeapon.h"

//CONSTRUCTOR / DESTRUCTOR
MeleeWeapon::MeleeWeapon(unsigned value, std::string texture_file)
	: Weapon(value, texture_file)
{
	this->type = ItemTypes::MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon()
{
}
