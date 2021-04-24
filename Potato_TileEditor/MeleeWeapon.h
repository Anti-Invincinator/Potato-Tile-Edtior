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
    MeleeWeapon(unsigned value, std::string texture_file);
    virtual ~MeleeWeapon();

   

    //FUNCTIONS
    virtual MeleeWeapon* clone() = 0;

    virtual void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void Render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

#endif // !MELEEWEAPON_H



