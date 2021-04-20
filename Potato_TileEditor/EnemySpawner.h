#ifndef ENEMY_SPAWNER
#define ENEMY_SPAWNER

class EnemySpawner
{
private:
	sf::RectangleShape shape;

	sf::Vector2i gridPosition;
	int type;
	int amount;
	int timerToSpawn;
	float maxDistance;

public:
	EnemySpawner(sf::Vector2i grid_position, float grid_size, int type, int amount, int time_to_spawn, float max_distance);
	virtual ~EnemySpawner();

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};

#endif // !ENEMY_SPAWNER



