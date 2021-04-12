#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

//Forward Declaration
class State;
class Gui;
class Pausemenu;
class TileMap;

class EditorState :
	public State
{

private:
	//Variables
	sf::View view;

	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;	

	sf::IntRect textureRect;
	bool collision;
	short type;
	float cameraSpeed;

	//Initializer Functions
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

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




