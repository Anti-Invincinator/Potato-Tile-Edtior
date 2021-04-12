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

	this->createHitboxComponent(this->sprite, 86.f, 75.f, 86.f, 111.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
}

Player::~Player()
{

}
//Functions

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
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
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->Play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(258.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->Play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->Play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->Play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
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

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->Render(target);
}

