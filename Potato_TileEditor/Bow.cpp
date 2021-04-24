#include "stdafx.h"
#include "Bow.h"

//CONSTRUCTOR / DESTRUCTOR
Bow::Bow(unsigned value, std::string texture_file)
	:RangedWeapon(value, texture_file)
{
	
}

Bow::~Bow()
{
}

Bow* Bow::clone()
{
	return new Bow(*this);
}

void Bow::Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
}

void Bow::Render(sf::RenderTarget& target, sf::Shader* shader)
{
}
