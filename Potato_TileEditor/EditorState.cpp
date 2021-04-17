#include "stdafx.h"
#include "EditorState.h"


//Initializer Functions
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 100.f;
	this->layer = 0;
}

void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f ,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	);
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Avenir-Black.otf"))
	{
		throw("ERROR::EDITOR_STATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initText()
{
	//REMOVE LATER
//Prints out the mouse position on screen

	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initPauseMenu()
{
   const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
   this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
   
   this->pmenu->addButton("QUIT", gui::p2pY(83.3f, vm), gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm), "Quit", gui::p2fontSize(vm, 80));
   this->pmenu->addButton("SAVE", gui::p2pY(55.5f, vm), gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm), "Save", gui::p2fontSize(vm, 80));
   this->pmenu->addButton("LOAD", gui::p2pY(27.7f, vm), gui::p2pX(15.6f, vm), gui::p2pY(7.8f, vm), "Load", gui::p2fontSize(vm, 80));
  
}

void EditorState::initButtons()
{

}

void EditorState::initGui()
{
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

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 1000.f, 700.f, 
		this->stateData->gridSize, this->tileMap->getTileTextureSheet(),
		this->font, "TS"
		);


}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");
}

//Constructor/Destructor

/* CONSTRUCTOR
* -Initialization Functions
* 1.Initializing Fonts
* 2.Initializing Keybinds
* 2.Initializing Buttons
*
* -Background Setup
* 1.Setting the size of the background
* 1.Setting the fill color of the background
*/

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}

/* DESTRUCTOR
*  1.Deleting Buttons
*  2.Deleting Pause Menu
*  3.Deleting Tile Map
*/

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;

	delete this->textureSelector;
}


//Functions
void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Move View
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}
	//Adding a tile on the tilemap
	if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) //when the mouse is not inside the side bar
		{
			if (!this->textureSelector->getActive())  //when texture selector is active
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
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
		if(this->type > 0)
		--this->type;
	}

}

void EditorState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality.*/
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt)
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
		"\nTiles: " << this->tileMap->getLayerSize(this->mousePosGrid.x, this->mousePosGrid.y, this->layer);
	this->cursorText.setString(ss.str());


}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("text.pemp");
	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("text.pemp");
}

void EditorState::Update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused 
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else   //Paused
	{
		this->pmenu->Update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
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

void EditorState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->Render(*target, this->mousePosGrid, nullptr, sf::Vector2f(), true);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused)   //Paused
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->Render(*target);
	}
	
}