#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Item.h"

class Item;

class MeleeWeapon :
    public Item
{
private:

protected:
    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;

    int damageMin;
    int damageMax;

public:
    //CONSTRUCTOR / DESTRUCTOR
    MeleeWeapon();
    virtual ~MeleeWeapon();

    //FUNCTIONS
    virtual void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void Render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

#endif // !MELEEWEAPON_H



