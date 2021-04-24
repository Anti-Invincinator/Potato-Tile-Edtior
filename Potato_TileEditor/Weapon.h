#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon :
    public Item
{
private:
    void initVariables();

protected:
    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;

    unsigned damageMin;
    unsigned damageMax;
    unsigned range;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

public:
    Weapon(unsigned value, std::string texture_file);
    virtual ~Weapon();

    //Accessors
    const unsigned& getRange() const;
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const bool getAttackTimer();

    //Functions
    virtual Item* clone();

    virtual void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif //!WEAPON_H
