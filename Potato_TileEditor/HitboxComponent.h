#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private :
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	//Constructor/Destructor
	HitboxComponent(sf::Sprite& sprite, 
		float offset_x , float offset_y, 
		float width, float height);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);

	void Update();
	void Render(sf::RenderTarget& target);
};

#endif // !HITBOXCOMPONENT_H



