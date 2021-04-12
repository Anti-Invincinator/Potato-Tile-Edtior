#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;


class Entity
{
private:
	//Initializer Functions
	void initVariables();

protected:
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public :
	Entity();
	virtual ~Entity();

	//Component Functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void Move(const float dir_x, const float dir_y, const float& dt);

	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget& target);
};

#endif // !ENTITY_H


