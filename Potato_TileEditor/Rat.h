#ifndef RAT_H
#define RAT_H

#include "Enemy.h"
#include "AIFollow.h"

class Rat :
    public Enemy
{
private:

    //Initializer Functions
    void initVariables();
    void initAnimations();
    void initAI();
    void initGui();

    sf::RectangleShape hpbar;

    AIFollow* follow;

public:

    //Constructor / Destructor
    Rat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
    virtual ~Rat();

    //Functions
    void takeDamage(const int damage);

    void updateAnimation(const float& dt);

    void Update(const float& dt, sf::Vector2f& mouse_pos_view);
    void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);
};

#endif // !RAT_H


