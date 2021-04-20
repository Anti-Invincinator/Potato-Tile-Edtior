#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy :
    public Entity
{
private:
    //Variables
    EnemySpawner& enemySpawner;

    //Initializer Functions
    void initVariables();
    void initAnimations();

public:
    //Constructor / Destructor
    Enemy(EnemySpawner& enemy_spawner, float x, float y, sf::Texture& texture_sheet);
    virtual ~Enemy();

    //Functions
    void updateAnimation(const float& dt);

    void Update(const float& dt, sf::Vector2f& mouse_pos_view);
    void Render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox);
};

#endif // !ENEMY_H



