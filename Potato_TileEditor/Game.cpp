#include "stdafx.h"
#include "Game.h"

//Static Functions

//Initiaization Functions
void Game::initVariables()
{
	this->window = nullptr;

	this->dt = 0.f;

	this->gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
	/*Create a SFML window using options from a window.ini file*/

}

void Game::initWindow()
{
	if(this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title, 
			sf::Style::Fullscreen, 
			this->gfxSettings.context_settings
		);
	else
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close, 
			this->gfxSettings.context_settings
		);


	this->window->setFramerateLimit(this->gfxSettings.framerate_limit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vertical_sync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = " ";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	//Debug
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));           //& is used due to them being pointers
}

//Constructors/Destructors
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

//Functions
void Game::updateDt()
{
	/*Updating delta time from previous render*/

	this->dt = this->dtClock.restart().asSeconds();

}

void Game::UpdateSFMLEvents()
{
	//sf::Event event;
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::Update()
{
	this->UpdateSFMLEvents();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->Update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	//Application end
	else
	{
		this->endApplication();

		//Closes the window which leads to the game being closed
		this->window->close();
	}
}

void Game::Render()
{
	this->window->clear();

	//Render Items

	//Render the top most state from the states stack if it isn't empty
	if (!this->states.empty())
		this->states.top()->Render(this->window);

	this->window->display();
}

void Game::Run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->Update();
		this->Render();
	}
}
