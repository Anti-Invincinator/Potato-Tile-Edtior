#include "stdafx.h"
#include "EnemySystem.h"


//Constructor / Destructor
EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures)
	: textures(textures), activeEnemies(activeEnemies)
{

}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float pos_x, const float pos_y)
{
	switch (type)
	{
	case EnemyTypes::RAT :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["RAT_SHEET"]));
		break;
	case EnemyTypes::SLIME :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["SLIME_SHEET"]));
		break;
	case EnemyTypes::SCORPION :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["SCORPION_SHEET"]));
		break;
	case EnemyTypes::SPIDER :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["SPIDER_SHEET"]));
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::Update(const float& dt)
{
}

void EnemySystem::Render(sf::RenderTarget* target)
{
}
