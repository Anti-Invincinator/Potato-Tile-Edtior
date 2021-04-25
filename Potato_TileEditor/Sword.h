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
    Sword(unsigned level, unsigned value, std::string texture_file, unsigned damage_min, unsigned damage_max, unsigned range);
    virtual ~Sword();

    //FUNCTIONS
    virtual Sword* clone();

    void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
    void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

#endif // !SWORD_H



