#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: stateData(state_data), tileMap(tile_map), editorStateData(editor_state_data)
{

}

EditorMode::~EditorMode()
{

}

const bool EditorMode::getKeytime()
{
	if (*this->editorStateData->keytime >= *this->editorStateData->keytimeMax)
	{
		*this->editorStateData->keytime = 0.f;
		return true;
	}

	return false;
}

std::string EditorMode::getTypeAsString(int type)
{
	std::string tile_type = "";
	switch (type)
	{
	case 0: tile_type = "Default"; 
		break;
	case 1: tile_type = "Damaging"; 
		break;
	case 2: tile_type = "Forward Layer";
		break;
	}

	return tile_type;
}
