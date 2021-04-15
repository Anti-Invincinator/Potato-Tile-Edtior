#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"

class Player;

class PlayerGUI
{
private :
	Player* player;

public:
	//Constructor / Destructor
	PlayerGUI(Player* player);
	~PlayerGUI();

	//Functions
	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};


#endif // !PLAYERGUI

