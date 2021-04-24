#include "stdafx.h"
#include "Enemy.h"

//Initializer functions
void Enemy::initVariables()
{
	this->giveExp = 10;
}

void Enemy::initAnimations()
{

}

//Constructor/Destructor
Enemy::Enemy()
{
	this->initVariables();
	this->initAnimations();
}

Enemy::~Enemy()
{

}

const AttributeComponent* Enemy::getAttributeComponent()
{
	if (this->attributeComponent)
		return this->attributeComponent;

	else
	{	
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
		
}

const unsigned& Enemy::getGiveExp()
{
	return this->giveExp;
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
		return this->attributeComponent->isDead();

	return false;
}

void Enemy::takeDamage(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}
