#include "stdafx.h"
#include "Enemy.h"

//Initializer functions
void Enemy::initVariables()
{
	this->giveExp = 10;
	this->damageTimerMax = 500;
}

void Enemy::initAnimations()
{

}

//Constructor/Destructor
Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile)
	: enemySpawnerTile(enemy_spawner_tile)
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

EnemySpawnerTile& Enemy::getEnemySpawnerTile()
{
	return this->enemySpawnerTile;
}

const bool Enemy::getDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

void Enemy::resetDamageTimer()
{
	this->damageTimer.restart();
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
		return this->attributeComponent->isDead();

	return false;
}

void Enemy::generateAttributes(const unsigned level)
{
	this->giveExp = level * (rand() % 5 + 1);
}

void Enemy::takeDamage(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}
