#include "stdafx.h"
#include "EnemySpawnerTile.h"


//Constructor / Destructor
EnemySpawnerTile::EnemySpawnerTile(
	int grid_x, int grid_y,
	float gridSizeF,
	const sf::Texture& texture,
	const sf::IntRect& texture_rect,
	int enemy_type,
	int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	: Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}

//Accessors
const std::string EnemySpawnerTile::getAsString() const
{
	/*
	x, y, z (done in  tilemap save)
	type,
	rect x, rect y,
	enemy type,
	enemy amount,
	enemy time to spawn,
	enemy max distance
	*/

	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->enemyAmount << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;

	return ss.str();
}

const bool& EnemySpawnerTile::getSpawned() const
{
	return this->spawned;
}

//Modifiers
void EnemySpawnerTile::setSpawned(const bool spawned)
{

}


//Functions
void EnemySpawnerTile::Update()
{

}

void EnemySpawnerTile::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
