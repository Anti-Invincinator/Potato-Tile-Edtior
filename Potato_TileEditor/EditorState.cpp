#include "stdafx.h"
#include "EditorState.h"


//Initializer Functions
void EditorState::initVariables()
{
	this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
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

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Avenir-Black.otf"))
	{
		throw("ERROR::EDITOR_STATE::COULD NOT LOAD FONT");
	}
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



}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFUALT_EDITOR_MODE;  
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
	this->initEditorStateData();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

	this->initModes();
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

	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))))
	{
		if (this->activeMode < this->modes.size() - 1)
		{
			this->activeMode++;
		}
		else
		{
			std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE!" << "\n";
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
	{
		if (this->activeMode > 0)
		{
			this->activeMode--;
		}
		else
		{
			std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE!" << "\n";
		}
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

void EditorState::updateModes(const float& dt)
{
	this->modes[this->activeMode]->Update(dt);
}

void EditorState::Update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateModes(dt);

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
	
}

void EditorState::renderModes(sf::RenderTarget& target)
{
	this->modes[this->activeMode]->Render(target);
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

	this->renderModes(*target);

	if (this->paused)   //Paused
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->Render(*target);
	}
	
}