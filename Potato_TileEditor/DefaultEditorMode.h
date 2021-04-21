#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode :
    public EditorMode
{
private :
	sf::Text cursorText;
	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;

	sf::IntRect textureRect;
	bool collision;
	short type;
	float cameraSpeed;
	int layer;
	bool tileAddLock;

	//Init Functions
	void initVariables();
	void initGui();

public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, sf::Font* font);
    virtual ~DefaultEditorMode();

	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void Update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
};

#endif // !DEFAULTEDITORMODE_H



