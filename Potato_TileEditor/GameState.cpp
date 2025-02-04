#include "stdafx.h"
#include "GameState.h"

//Initializer Functions
void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 1.25f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 1.25f
		)
	);

	this->view.setCenter(
		sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

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
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE_SHEET";
	}

	//Loading Enemy Textures
	if (!this->textures["RAT_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT_TEXTURE_SHEET";
	}
	if (!this->textures["SLIME_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/blob.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SLIME_TEXTURE_SHEET";
	}
	if (!this->textures["SCORPION_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/scorpion.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SCORPION_TEXTURE_SHEET";
	}
	if (!this->textures["SPIDER_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/spider.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SPIDER_TEXTURE_SHEET";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(83.3f, vm), gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm), "Quit", gui::p2fontSize(vm, 80));
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vert_shader.vert", "frag_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initKeyTimer()
{
	this->keyTimeMax = 400.f;
	this->keyTimer.restart();
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void GameState::initPlayer()
{
	this->player = new Player(220, 200, this->textures["PLAYER_SHEET"]);
}
       
void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap("text.pemp");
}

void GameState::initSystems()
{
	this->textTagSystem = new TextTagSystem("Fonts/Karantina-Bold.ttf");
}

//CONSTRUCTOR / DESTRUCTOR
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initKeyTimer();
	this->initPlayer();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap();

	this->initSystems();
}

GameState::~GameState()
{
	delete this->player;
	delete this->playerGUI;
	delete this->pmenu;
	delete this->enemySystem;
	delete this->tileMap;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}

	delete this->textTagSystem;
}

//Accessors
const bool GameState::getKeytime()
{
	if (this->keyTimer.getElapsedTime().asMilliseconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}

//Functions
void GameState::updateView(const float& dt)
{
		this->view.setCenter(
			std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
			std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
		);


	if (this->tileMap->getMaxSizeGridF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeGridF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeGridF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeGridF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeGridF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeGridF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

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

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_TAB"))) && this->getKeytime())
	{
		this->playerGUI->toggleCharacterTab(); 
	}
}

void GameState::updatePausedMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayer(const float& dt)
{
	this->player->Update(dt, this->mousePosView);
}

void GameState::updateCombatAndEnemies(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getWeapon()->getAttackTimer())
		this->player->setInitAttack(true);

	unsigned index = 0;
	//Update all enemies
	for (auto* enemy : this->activeEnemies)
	{
		enemy->Update(dt, this->mousePosView);

		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);

		if(this->player->getInitAttack())
			this->updateCombat(enemy, index, dt);

		//DANGEROUS
		if(enemy->isDead())
		{
			this->player->gainExp(enemy->getGiveExp());
			this->textTagSystem->addTextTag(EXPERIENCE_TAG, this->player->getCenter().x, this->player->getCenter().y, static_cast<int>(enemy->getGiveExp()), "+", "EXP");

			this->enemySystem->removeEnemy(index);

			--index;
		}

		++index;
	}

	this->player->setInitAttack(false);
}

void GameState::updateCombat(Enemy* enemy, const int index, const float& dt)
{		
	if ( enemy->getGlobalBounds().contains(this->mousePosView) &&
		enemy->getDistance(*this->player) < this->player->getWeapon()->getRange() &&
		enemy->getDamageTimerDone())
	{	
		int damage = static_cast<int>(this->player->getWeapon()->getDamage());
		enemy->takeDamage(damage);
		enemy->resetDamageTimer();
		this->textTagSystem->addTextTag(NEGATIVE_TAG, enemy->getCenter().x, enemy->getCenter().y, damage, "-");	
	}
}

void GameState::Update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused Update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->updateCombatAndEnemies(dt);

		this->updatePlayer(dt);

		this->updatePlayerGUI(dt);

		//Update Systems
		this->textTagSystem->Update(dt);
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

	this->renderTexture.clear();
		
	this->renderTexture.setView(this->view);
	this->tileMap->Render(
		this->renderTexture,
		this->viewGridPosition,
		&this->core_shader,
		this->player->getCenter(),
		false
	);

	for (auto *i : this->activeEnemies)
	{
		i->Render(this->renderTexture, &this->core_shader, this->player->getCenter(), true);
	}

	this->player->Render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);

	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());

	this->textTagSystem->Render(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());  //To Render it on Window and not on map
	this->playerGUI->Render(this->renderTexture);

	if (this->paused) //Pause Menu Render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->Render(this->renderTexture);
	}

	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite); 
}