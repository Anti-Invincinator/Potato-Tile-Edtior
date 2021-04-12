#ifndef SETTINGS_STATE
#define SETTINGS_STATE

#include "State.h"
#include "Gui.h"
#include "GraphicsSettings.h"

class State;
class Gui;
class GraphicsSettings;

class SettingsState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropdDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//Accessors

	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void Update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
};

#endif // !SETTINGS_STATE



