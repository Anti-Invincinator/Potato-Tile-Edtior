#include "stdafx.h"
#include "GameState.h"

//Initializer Functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Avenir-Black.otf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 900.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/TILESHEET.png");
}

// Constructor/Destructor
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pmenu;
	delete this->tileMap;
}

//Functions
void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{

	//Updates Player Movement Inpit
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->Move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->Move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->Move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->Move(0.f, 1.f, dt);
	}
	
}

void GameState::updatePausedMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::Update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused Update
	{
		this->updatePlayerInput(dt);

		this->player->Update(dt);
	}
	else  //Paused Update
	{
		this->pmenu->Update(this->mousePosWindow);
		this->updatePausedMenuButtons();
	}
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
		//this->tileMap->Render(*target);

		this->player->Render(*target);

		if (this->paused) //Pause Menu Render
		{
			this->pmenu->Render(*target);
		}
}
