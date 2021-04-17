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

	this->createHitboxComponent(this->sprite, 10.f, 5.f, 44.f, 54.f);
	this->createMovementComponent(200.f, 1500.f, 900.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 16.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 16.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 16.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 16.f, 12, 1, 15, 1, 64, 64);
	//this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
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
	this->attributeComponent->hitpoints -= hp;

	if (this->attributeComponent->hitpoints < 0)
		this->attributeComponent->hitpoints = 0;
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hitpoints += hp;

	if (this->attributeComponent->hitpoints > this->attributeComponent->hitpointsMax)
		this->attributeComponent->hitpoints = this->attributeComponent->hitpointsMax;
}

void Player::gainEXP(const int exp)
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
		//Set origin depending upon the direction
		if (this->sprite.getScale().x > 0.f)  //Facing Left
		{
			this->sprite.setOrigin(96.f, 0.f);
		}
		else //Facing Right
		{
			this->sprite.setOrigin(258.f + 96.f, 0.f);
		}

		if (this->animationComponent->Play("ATTACK", dt, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f)  //Facing Left
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else //Facing Right
			{
				this->sprite.setOrigin(258.f, 0.f);
			}
		}
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
void Player::Update(const float& dt)
{
	this->movementComponent->Update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->Update();
}

void Player::Render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());
		target.draw(this->sprite, shader);
	}
	else
		target.draw(this->sprite);

	if(show_hitbox)
	this->hitboxComponent->Render(target);
}