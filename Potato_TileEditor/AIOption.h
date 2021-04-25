#ifndef AIOPTION_H
#define AIOPTION_H

#include "Entity.h"

class AIOption
{
protected:

	Entity& self;
	Entity& entity;

public:
	AIOption(Entity& self, Entity& entity)
		: self(self), entity(entity)
	{

	}

	virtual ~AIOption();

	virtual void Update(const float& dt) = 0;
};

#endif // !AIOPTION_H



