#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "EnemySpawnerTile.h"
#include "Rat.h"

enum EnemyTypes { RAT = 0, SLIME, SCORPION, SPIDER };

class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;

public:

	//Constructor / Destructor
	EnemySystem(std::vector<Enemy*>& activeEnemies,
		std::map<std::string, sf::Texture>& textures);
	virtual ~EnemySystem();

	//Accessors


	//Modifiers


	//Functions
	void createEnemy(const short type, const float pos_x, const float pos_y);

	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
};


#endif // !ENEMYSYSTEM_H


