#include "stdafx.h"
#include "EnemySystem.h"


//Constructor / Destructor
EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(activeEnemies), player(player)
{

}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float pos_x, const float pos_y, EnemySpawnerTile& enemy_spawner_tile)
{
	switch (type)
	{
	case EnemyTypes::RAT :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["RAT_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTypes::SLIME :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["SLIME_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTypes::SCORPION :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["SCORPION_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTypes::SPIDER :
		this->activeEnemies.push_back(new Rat(pos_x, pos_y, this->textures["SPIDER_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::Update(const float& dt)
{
}

void EnemySystem::Render(sf::RenderTarget* target)
{
}
