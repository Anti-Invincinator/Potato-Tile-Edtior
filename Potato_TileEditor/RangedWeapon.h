#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Weapon.h"

class RangedWeapon :
    public Weapon
{
protected:

public:
    //CONSTRUCTOR / DESTRUCTOR
    RangedWeapon(unsigned level, unsigned value, std::string texture_file);
    virtual ~RangedWeapon();

    virtual RangedWeapon* clone() = 0;
    void generate(const unsigned level_min, const unsigned level_max);

    virtual void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void Render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

#endif // !RANGEDWEAPON_H



