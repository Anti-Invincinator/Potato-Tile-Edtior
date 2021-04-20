#include "stdafx.h"
#include "EnemySpawner.h"


//Constructor / Destructor
EnemySpawner::EnemySpawner(sf::Vector2i grid_position, float grid_size, int type, int amount, int time_to_spawn, float max_distance)
{
	this->shape.setSize(sf::Vector2f(grid_size, grid_size));
	this->shape.setFillColor(sf::Color::Red);

	this->gridPosition = grid_position;
	this->type = type;
	this->amount = amount;
	this->timerToSpawn = time_to_spawn;
	this->maxDistance = max_distance;
}

EnemySpawner::~EnemySpawner()
{
}


//Functions
void EnemySpawner::Update(const float& dt)
{
}

void EnemySpawner::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
