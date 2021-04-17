#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "SettingsState.h"
#include "EditorState.h"
#include "Gui.h"
#include "GraphicsSettings.h"

class GameState;
class SettingsState;
class EditorState;
class Gui;
class GraphicsSettings;

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void Update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
};

#endif // !MAINMENUSTATE_H



