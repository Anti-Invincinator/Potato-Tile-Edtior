#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorMode.h"

//Forward Declaration
class State;
class StateData;
class Gui;
class Pausemenu;
class TileMap;
class Tile;
class EditorMode;

enum EditorModes {DEFAULT_MODE = 0, ENEMY_MODE};

class EditorState :
	public State
{

private:
	//Variables
	sf::View view;
	float cameraSpeed;
	sf::Font font;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	std::vector<EditorMode*> modes;

	//Initializer Functions
	void initVariables();
	void initView();
	void initFonts();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

	void initModes();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//Functions
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void Update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
};

#endif // !EDITORSTATE_H