#include "stdafx.h"
#include "RangedWeapon.h"


//CONSTRUCTOR / DESTRUCTOR
RangedWeapon::RangedWeapon(unsigned level, unsigned value, std::string texture_file)
	: Weapon(level, value, texture_file)
{
	this->type = ItemTypes::RANGEDWEAPON;
}

RangedWeapon::~RangedWeapon()
{
}

void RangedWeapon::generate(const unsigned level_min, const unsigned level_max)
{
	
}
