#include "stdafx.h"
#include "Sword.h"

//CONSTRUCTOR / DESTRUCTOR
Sword::Sword(unsigned level, unsigned value, std::string texture_file, unsigned damage_min, unsigned damage_max, unsigned range)
	:MeleeWeapon(level, value, texture_file, damage_min, damage_max, range)
{
	this->weapon_sprite.setOrigin(
		this->weapon_sprite.getGlobalBounds().width / 2.f,
		this->weapon_sprite.getGlobalBounds().height /// 2.f + 10.f
	);
}

Sword::~Sword()
{
}

Sword* Sword::clone()
{
	return new Sword(*this);
}

//FUNCTIONS
void Sword::Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
	//Update visual weapon
	this->weapon_sprite.setPosition(center);

	float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265f;

	float deg = atan2(dY, dX) * 180.f / PI;

	if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax / 4)
	{
		float len = sqrt(pow(dX, 2) + pow(dY, 2));
		sf::Vector2f normVec(dX / len, dY / len);

		this->weapon_sprite.setPosition(center.x + normVec.x * 10.f, center.y + normVec.y * 10.f);
	}
	else
		this->weapon_sprite.setRotation(deg + 90.f);
}

void Sword::Render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
		target.draw(this->weapon_sprite, shader);

	else
		target.draw(this->weapon_sprite);
}
