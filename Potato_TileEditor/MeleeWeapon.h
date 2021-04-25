#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"

class MeleeWeapon :
    public Weapon
{
private:

protected:


public:
    //CONSTRUCTOR / DESTRUCTOR
    MeleeWeapon(unsigned level, unsigned value, std::string texture_file, unsigned damage_min, unsigned damage_max, unsigned range);
    virtual ~MeleeWeapon();

   

    //FUNCTIONS
    virtual MeleeWeapon* clone() = 0;
    void generate(const unsigned level_min, const unsigned level_max);

    virtual void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void Render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

#endif // !MELEEWEAPON_H



