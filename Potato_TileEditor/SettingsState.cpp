#include "stdafx.h"
#include "SettingsState.h"

//Initializer Functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

//Functions
void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Avenir-Black.otf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
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
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(72.9f, vm), gui::p2pY(81.4f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::p2fontSize(vm, 75),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(62.5f, vm), gui::p2pY(81.4f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Apply", gui::p2fontSize(vm, 75),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)
	);

	//Modes
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	//DropDownLists
	this->dropdDownLists["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(41.6f, vm), gui::p2pY(41.6f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(4.6f, vm),
		font, modes_str.data(), modes_str.size()
	);

	//Text Init
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(41.6f, vm)));
	this->optionsText.setCharacterSize(gui::p2fontSize(vm, 100));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);
}

void SettingsState::resetGui()
{
	/*
	* Clears the GUI elements and reinitializes them
	*
	* @return void
	*/

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropdDownLists.begin();
	for (it2 = this->dropdDownLists.begin(); it2 != this->dropdDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropdDownLists.clear();

	this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropdDownLists.begin();
	for (it2 = this->dropdDownLists.begin(); it2 != this->dropdDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/*Updates all gui elements in the state and handles their functionality.*/
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosWindow);
	}

	//Quitting the Settings
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}	

	//Apply Selected Settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST
		this->stateData->gfxSettings->resolution = this->modes[this->dropdDownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
		this->resetGui();
	}

	//Drop Down Lists
	for (auto& it : this->dropdDownLists)
	{
		it.second->Update(this->mousePosWindow, dt);
	}

	//Drop Down List(s) Functionality

}

void SettingsState::Update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}

	for (auto& it2 : this->dropdDownLists)
	{
		it2.second->Render(target);
	}
}

void SettingsState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

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
