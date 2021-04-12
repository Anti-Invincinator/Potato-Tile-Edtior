#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include"Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	void Clear();

	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	unsigned layers;
	std::vector< std::vector< std::vector< Tile* > > > map;
	sf::Texture tileTextureSheet;
	std::string textureFile;
	sf::RectangleShape collisionBox;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

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

	void updateCollision(Entity* entity);

	void Update();
	void Render(sf::RenderTarget& target, Entity* entity = nullptr);


};

#endif // !TILEMAP_H



