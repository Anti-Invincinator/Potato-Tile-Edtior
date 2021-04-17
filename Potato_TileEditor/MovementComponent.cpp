#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), 
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

//ACCESSORS
const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (this->velocity.x != 0.f && this->velocity.y != 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;

	default:
		break;
	}

	return false;
}

void MovementComponent::stopVelocity()
{
	/* Resets the velocity to 0.*/
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	/* Resets the velocity x to 0.*/
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/* Resets the velocity y to 0.*/
	this->velocity.y = 0.f;
}


//Functions
void MovementComponent::Move(const float dir_x, const float dir_y, const float& dt)
{
	/*Acceleration a sprite until it reaches the max velocity.*/

	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;
}


void MovementComponent::Update(const float& dt)
{
	/*Decelerates the psrite and control the maximum velocity.
	  Moves the sprite
	*/
	if (this->velocity.x > 0.f) //Check for positive x
	{
		//Max Velocity Check 
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) //Check for negative x
	{
		//Max Velocity Check X negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration x negative
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //Check for positive y
	{
		//Max Velocity Check 
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //Check for negative y
	{
		//Max Velocity Check Y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration x negative
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}
	//Final Move
	this->sprite.move(this->velocity * dt);  //uses velocity
}