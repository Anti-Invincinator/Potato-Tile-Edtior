#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy :
    public Entity
{
protected:
    //Variables
    EnemySpawnerTile& enemySpawnerTile;
    unsigned giveExp;
    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;

    //Initializer Functions
    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:
    //Constructor / Destructor
    Enemy(EnemySpawnerTile& enemy_spawner_tile);
    virtual ~Enemy();

    //Accessors
    virtual const AttributeComponent* getAttributeComponent();
    const unsigned& getGiveExp();
    EnemySpawnerTile& getEnemySpawnerTile();
    const bool getDamageTimerDone() const;

    //Modifiers
    void resetDamageTimer();

    //Functions
    virtual void generateAttributes(const unsigned level);

    virtual void takeDamage(const int damage);
    virtual const bool isDead() const;

    virtual void updateAnimation(const float& dt) = 0;

    virtual void Update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
    virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

#endif // !ENEMY_H



