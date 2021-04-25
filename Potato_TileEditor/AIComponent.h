#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "AIFollow.h"
#include "Entity.h"

class AIComponent
{
private:
	Entity& entity;
	Entity& self;

public:
	AIComponent(Entity& self, Entity& entity);
	virtual ~AIComponent();

	void Update(const float& dt);
};
#endif // !AICOMPONENT_H

