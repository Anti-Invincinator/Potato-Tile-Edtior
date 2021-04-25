#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Entity.h"
#include "Items.h"

class Player :
    public Entity
{
private:
    //Variables
    Inventory* inventory;

    bool initAttack;
    bool attacking;
    Sword* sword;

    //Initializer functions
    void initVariables();
    void initComponents();
    void initAnimations();
    void initAttributes();
    void initInventory();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();
    Weapon* getWeapon() const;
    const bool& getInitAttack() const;
    const std::string toStringCharacterTab() const;

    //Modifiers
    void setInitAttack(const bool initAttack);

    //Functions
    void loseHP(const int hp);
    void loseEXP(const int exp);
    void gainHP(const int hp);
    void gainExp(const int exp);

    void updateAnimation(const float& dt);
    virtual void Update(const float& dt, sf::Vector2f& mouse_pos_view);
    void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif // !PLAYER_H