#ifndef AIFOLLOW_H
#define AIFOLLOW_H

#include "AIOption.h"
class AIFollow :
    public AIOption
{
private:

public:
    AIFollow(Entity& self, Entity& entity);
    virtual ~AIFollow();

    void Update(const float& dt);
};


#endif // !AIFOLLOW_H


