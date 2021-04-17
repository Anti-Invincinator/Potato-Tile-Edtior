#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class State;
class PauseMenu;
class TileMap;
class Player;
class PlayerGUI;

class GameState : public State
{
private :
	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	sf::Shader core_shader;

	Player* player;
	PlayerGUI* playerGUI;
	sf::Texture texture;

	TileMap* tileMap;

	//Initializer Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayer();
	void initPlayerGUI();
	void initTileMap();

public :
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePausedMenuButtons();
	void updateTileMap(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

#endif //GAMESTATE_H