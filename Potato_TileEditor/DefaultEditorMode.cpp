#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT_TILE;
	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultEditorMode::initGui()
{
	//Text
	this->cursorText.setFont(*this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);


	//General GUI
	this->sidebar.setSize(sf::Vector2f(100.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);


	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 100));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		20.f, 20.f, 1000.f, 700.f,
		this->stateData->gridSize, this->tileMap->getTileTextureSheet(),
		*this->font, "TS"
	);

	//Buttons
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, sf::Font* font)
	: EditorMode(state_data, tile_map, font)
{
	this->initVariables();
	this->initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
	delete this->textureSelector;
}

//Functions
void DefaultEditorMode::updateInput(const float& dt)
{
	//Adding a tile on the tilemap
	if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) //when the mouse is not inside the side bar
		{
			if (!this->textureSelector->getActive())  //when texture selector is active
			{
				if (this->tileAddLock)
				{
					if (this->tileMap->isTileEmpty(this->mousePosGrid.x, this->mousePosGrid.y, 0))
						this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
				}
				else
				{
					this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
				}

			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}

		//Removing a tile on the tilemap
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
		{
			if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
				if (!this->textureSelector->getActive())
					this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	}

	//Toggle Collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeytime())
	{
		//ADD A MAX LIMIT!!!!
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeytime())
	{
		if (this->type > 0)
			--this->type;
	}

	//Set lock on/off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_TILE_LOCK"))) && this->getKeytime())
	{
		if (this->tileAddLock)
			this->tileAddLock = false;
		else
			this->tileAddLock = true;
	}
}

void DefaultEditorMode::updateGui(const float& dt)
{
	this->textureSelector->Update(this->mousePosWindow, dt);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	//Mouse Cursor Text
	this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y - 20.f);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\nCollision: " << this->collision <<
		"\nType: " << this->type <<
		"\nTiles: " << this->tileMap->getLayerSize(this->mousePosGrid.x, this->mousePosGrid.y, this->layer) <<
		"\nTile Lock: " << this->tileAddLock;

	this->cursorText.setString(ss.str());
}

void DefaultEditorMode::Update(const float& dt)
{

}

void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
/*Heirarchy
 ~SelectorRect
 ~TextureSelector
 ~CursorText
*/

	if (!this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->Render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorText);
}

void DefaultEditorMode::Render(sf::RenderTarget* target)
{

}
