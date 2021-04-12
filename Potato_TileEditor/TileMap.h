#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class Tile;

class TileMap
{
private:
	void Clear();

	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector< std::vector< std::vector< Tile* > > > map;
	sf::Texture tileTextureSheet;
	std::string textureFile;

public:
	//Constructor/Destructor
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileTextureSheet() const;

	//Functions
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void Update();
	void Render(sf::RenderTarget& target);


};

#endif // !TILEMAP_H



