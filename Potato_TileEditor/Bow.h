#ifndef BOW_H
#define BOW_H

#include "RangedWeapon.h"

class RangedWeapon;

class Bow :
    public RangedWeapon
{
private:

public:
    //CONSTRUCTOR / DESTRUCTOR
    Bow(unsigned level, unsigned value, std::string texture_file);
    virtual ~Bow();

    //Functions
    virtual Bow* clone();

    virtual void Update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
    virtual void Render(sf::RenderTarget& target, sf::Shader* shader);
};
#endif // !BOW_H



