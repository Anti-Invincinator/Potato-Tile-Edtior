#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "Gui.h"

class Player;
class sf::RectangleShape;
class sf::Font;

class PlayerGUI
{
private :
	Player* player;

	sf::VideoMode& vm;

	sf::Font font;

	//Level
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;

	//EXP Bar
	std::string expBarString;
	sf::Text expBarText;
	float expBarWidth;
	sf::RectangleShape expBarBack;
	sf::RectangleShape expBar;

	//HP Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBar;

	//Initializer Functions
	void initFont();
	void initLevelBar();
	void initHPBar();
	void initEXPBar();

public:
	//Constructor / Destructor
	PlayerGUI(Player* player, sf::VideoMode& vm);
	~PlayerGUI();

	//Functions
	void updateHPBar();
	void renderHPBar(sf::RenderTarget& target);
	void updateEXPBar();
	void renderEXPBar(sf::RenderTarget& target);
	void updateLevelBar();
	void renderLevelBar(sf::RenderTarget& target);

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};


#endif // !PLAYERGUI