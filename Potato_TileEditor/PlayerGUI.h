#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "PlayerGUITab.h"

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
	gui::ProgressBar* expBar;

	//HP Bar
	gui::ProgressBar* hpBar;

	//Tabs
	PlayerGUITab* playerTabs;

	//Initializer Functions
	void initFont();
	void initLevelBar();
	void initHPBar();
	void initEXPBar();
	void initPlayerTab(sf::VideoMode& vm, sf::Font font, Player& player);


public:
	//Constructor / Destructor
	PlayerGUI(Player* player, sf::VideoMode& vm);
	~PlayerGUI();

	//Accessors
	const bool getTabsOpen() const;
	void toggleCharacterTab();

	//Functions

	//HUD
	void updateHPBar();
	void renderHPBar(sf::RenderTarget& target);
	void updateEXPBar();
	void renderEXPBar(sf::RenderTarget& target);
	void updateLevelBar();
	void renderLevelBar(sf::RenderTarget& target);


	void updatePlayerTabs();
	void renderPlayerTabs(sf::RenderTarget& target);

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};


#endif // !PLAYERGUI