#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "Tile.h"

class Tile;

class EnemySpawnerTile
	:public Tile
{
private:
	int enemyType;
	int enemyAmount;
	int enemyCounter;
	sf::Clock enemySpawnTimer;
	sf::Int32 enemyTimeToSpawn;
	float enemyMaxDistance;
	bool spawned;

	//Spawn Timer

public:
	EnemySpawnerTile(int grid_x, int grid_y,
		float gridSizeF,
		const sf::Texture& texture,
		const sf::IntRect& texture_rect,
		int enemy_type,
		int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawnerTile();

	//Accessors
	virtual const std::string getAsString() const;
	const bool& getSpawned() const;
	const int& getEnemyCounter() const;
	const int& getEnemyAmount() const;

	//Modifiers
	void setSpawned(const bool spawned);
	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	//Functions
	const bool canSpawn() const;
	

	void Update();
	void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_position = sf::Vector2f());
};

#endif // !ENEMY_SPAWNER_TILE_H



