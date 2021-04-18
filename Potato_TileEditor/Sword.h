#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword :
    public MeleeWeapon
{
private:

public:
    //CONSTRUCTOR / DESTRUCTOR
    Sword();
    virtual ~Sword();

    //FUNCTIONS
    void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
    void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

#endif // !SWORD_H



