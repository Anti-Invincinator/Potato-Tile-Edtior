#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class TileMap;
class Tile;

class EditorMode
{
protected :
	StateData* stateData;
	TileMap* tileMap;
	sf::Font* font;

public:
	EditorMode(StateData* state_data, TileMap* tile_map, sf::Font* font);
	virtual ~EditorMode();

	//Functions
	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;

	virtual void renderGui(sf::RenderTarget& target) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
};

#endif // !EDITORMODE_H



