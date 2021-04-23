#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Sword.h"

class Entity;
class Sword;

class Player :
    public Entity
{
private:
    //Variables
    bool attacking;
    Sword sword;

    //Initializer functions
    void initVariables();
    void initComponents();
    void initAnimations();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();

    //Functions
    void loseHP(const int hp);
    void loseEXP(const int exp);
    void gainHP(const int hp);
    void gainExp(const int exp);

    void updateAttack();
    void updateAnimation(const float& dt);
    virtual void Update(const float& dt, sf::Vector2f& mouse_pos_view);
    void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif // !PLAYER_H