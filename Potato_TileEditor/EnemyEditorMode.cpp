#include "stdafx.h"
#include "EnemyEditorMode.h"

//Init Functions
void EnemyEditorMode::initVariables()
{
	this->enemyType = 0;
	this->enemyAmount = 1;
	this->enemyTimeToSpawn = 20;
	this->enemyMaxDistance = 1000.f;
}


void EnemyEditorMode::initGui()
{
	//Text
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);


	//General GUI
	this->sidebar.setSize(sf::Vector2f(100.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);


	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 100));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	//Buttons
}

// Constructor / Destructor
EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
 : EditorMode(state_data, tile_map, editor_state_data)
{
	this->initVariables();
	this->initGui();
}

EnemyEditorMode::~EnemyEditorMode()
{

}


//Functions
void EnemyEditorMode::updateInput(const float& dt)
{
	//Adding a tile on the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) //when the mouse is not inside the side bar
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect,
				this->enemyType, this->enemyAmount, this->enemyTimeToSpawn, this->enemyMaxDistance);
		}
	}

	//Removing a tile on the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::ENEMYSPAWNER);
		}
	}

	//Enemy Spawner Data
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			if (this->enemyType > 0)
				this->enemyType--;
		}
		else if (this->enemyType < 4)
			this->enemyType++;
		else
			this->enemyType = 0;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("AMOUNT_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			if (this->enemyAmount > 0)
				this->enemyAmount--;
		}
		else if (this->enemyAmount < 10)
			this->enemyAmount++;
		else
			this->enemyAmount = 0;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TTS_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			if (this->enemyTimeToSpawn > 0)
				this->enemyTimeToSpawn--;
		}
		else if (this->enemyTimeToSpawn < 10)
			this->enemyTimeToSpawn++;
		else
			this->enemyTimeToSpawn = 0;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("MD_UP"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			if (this->enemyMaxDistance > 0)
				this->enemyMaxDistance -= 50;
		}
		else if (this->enemyMaxDistance < 1000)
			this->enemyMaxDistance += 50;
		else
			this->enemyMaxDistance = 0;
	}
}


void EnemyEditorMode::updateGui(const float& dt)
{
	this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);

	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 20.f);
	
	//Mouse Cursor Text
	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 20.f);
	std::stringstream ss;
	ss <<
		"\nEnemy Type: " << this->enemyType <<
		"\nEnemy Amount: " << this->enemyAmount <<
		"\nEnemy TimetoSpawn : " << this->enemyTimeToSpawn <<
		"\nEnemy MaxDistance : " << this->enemyMaxDistance;

	this->cursorText.setString(ss.str());
}

void EnemyEditorMode::Update(const float& dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target)
{
	target.setView(*this->editorStateData->view);
	target.draw(this->selectorRect);
	target.draw(this->cursorText);

	target.setView(target.getDefaultView());
	target.draw(this->sidebar);
}

void EnemyEditorMode::Render(sf::RenderTarget& target)
{
	this->renderGui(target);
}
