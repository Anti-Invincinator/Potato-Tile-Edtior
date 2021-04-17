#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}

//Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(200.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);

	//Visual Weapon
	if (!this->weapon_texture.loadFromFile("Resources/Images/Sprites/Player/sword.png"))
		std::cout << "ERROR :: PLAYER :: WAS NOT ABLE TO LOAD SWORD WEAPON TEXTURE";

	this->weapon_sprite.setTexture(this->weapon_texture);

	this->weapon_sprite.setOrigin(
		this->weapon_sprite.getGlobalBounds().width / 2.f,
		this->weapon_sprite.getGlobalBounds().height /// 2.f + 10.f
	);
}

Player::~Player()
{

}

//Accessors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	//Attack Animation
	//Animate and Check for animation end
	if (this->attacking)
	{

	}

	//Movement Animations
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->Play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->Play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->Play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->Play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->Play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}


/*
	Updating Player
	1.updating movement Component (called from Entity Class)
	2.checking for attack input
	3.updating player animations
	4.updating hitox component (called from Entity Class)
*/
void Player::Update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->Update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->Update();


	//Update visual weapon
	this->weapon_sprite.setPosition(this->getCenter());

	float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265;

	float deg = atan2(dY, dX) * 180 / PI;

	this->weapon_sprite.setRotation(deg + 90);
}

void Player::Render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());
		target.draw(this->weapon_sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
		target.draw(this->weapon_sprite);
	}

	if(show_hitbox)
	this->hitboxComponent->Render(target);
}