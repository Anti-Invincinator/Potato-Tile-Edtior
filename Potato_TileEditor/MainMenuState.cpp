#include "stdafx.h"
#include "MainMenuState.h"

//Initializer Functions
void MainMenuState::initVariables()
{

}

//Functions
void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Avenir-Black.otf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/mainmenu.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Buttons
	this->buttons["GAME_STATE"] = new gui::Button (
		gui::p2pX(42.f, vm), gui::p2pY(26.8f, vm),															// posX, posY
		gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm),           													//sizeX, sizeY
		&this->font, "Start Game", gui::p2fontSize(vm, 100),																  // font, text, font size
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),		  // idle, hover, pressed Text Color
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)			// idle, hover, pressed Button Color  (0 in alpha to make it a transparent button)
	);		  

	this->buttons["SETTINGS_STATE"] = new gui::Button (
		gui::p2pX(42.f, vm), gui::p2pY(40.7f, vm),
		gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm),
		&this->font, "Settings", gui::p2fontSize(vm, 100),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EDITOR_STATE"] = new gui::Button (
		gui::p2pX(42.f, vm), gui::p2pY(54.6f, vm),
		gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm),
		&this->font, "Editor", gui::p2fontSize(vm, 100),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EXIT_STATE"] = new gui::Button (
		gui::p2pX(42.f, vm), gui::p2pY(68.5f, vm),
		gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm),
		&this->font, "Quit", gui::p2fontSize(vm, 100),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)
	);


}

void MainMenuState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}

//Constructor/Destructor

/* CONSTRUCTOR
* -Initialization Functions
* 1.Initializing Fonts
* 2.Initializing Keybinds
* 3.Initializing Buttons
* 
* -Background Setup
* 1.Setting the size of the background
*/
MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();


	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)
		)
	);
}

/* DESTRUCTOR
*  1.Deleting Buttons
*/
MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions
void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality.*/
	for (auto &it : this->buttons)
	{
		it.second->Update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}
	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}
	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}
	//Quitting the Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}
	 
void MainMenuState::Update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	//REMOVE LATER
	//Prints out the mouse position on screen
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}
