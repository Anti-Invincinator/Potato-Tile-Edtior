#include "stdafx.h"
#include "SettingsState.h"

//Initializer Functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/mainmenu.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
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
	this->buttons["BACK"] = new gui::Button(
		1400.f, 880.f, 250.f, 65.f,
		&this->font, "Back", 30,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new gui::Button(
		1200.f, 880.f, 250.f, 65.f,
		&this->font, "Apply", 30,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0)
	);

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropdDownLists["RESOLUTION"] = new gui::DropDownList(800.f, 450.f, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 450.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);
}


SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
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
