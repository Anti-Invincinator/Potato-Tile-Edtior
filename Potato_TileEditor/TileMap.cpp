#include "stdafx.h"
#include "TileMap.h"

void TileMap::Clear()
{
	if (!this->map.empty())
	{
		for (size_t x = 0; x < this->map.size(); x++)
		{
			for (size_t y = 0; y < this->map[x].size(); y++)
			{
				for (size_t z = 0; z < this->map[x][y].size(); z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = nullptr;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}
}

//Constructor / Destructor
TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	//Culling
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	//use reserve not resize  (for push_back)
	//if using resize (size, default value) and remove the push back function  !!!!!Resize resizes the internal array and adds default values

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());     //resizes the map and adds default Tile()

	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if (!this->tileTextureSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURE SHEET::FILENAME: "<<texture_file << "\n";

	//Collision Box
	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::TileMap(const std::string file_name)
{
	//Culling
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(file_name);

	//Collision Box
	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->Clear();
}

const bool TileMap::isTileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && x < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)
	{
		return this->map[x][y][z].empty();
	}

	return false;
}

//Accessors
const sf::Texture* TileMap::getTileTextureSheet() const
{
	return &this->tileTextureSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}

	return -1;
}

const sf::Vector2i& TileMap::getMaxSizeWorldGrid() const
{
	return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeGridF() const
{
	return this->maxSizeWorldF;
}

//Functions
void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the tile map to a text-file.
	Format: 
	Basic:
	Size x y
	gridSize
	layers
	texture file 

	All Tiles:
	type
	gridPos x y 
	layer(of all tiles),
	Texture rect x y,
	collision,
	tile_specific
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		//Iterate through each induvidual tile
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString()
								<< "\n";													 //MAKE SURE THE LAST SPACE IS NOT SAVED TO PREVENT ISSUES from getline(), cin
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;


		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		this->layers = layers;
		this->textureFile = texture_file;

		this->Clear();

		//use reserve not resize  (for push_back)
		//if using resize (size, default value) and remove the push back function  !!!!!Resize resizes the internal array and adds default values

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());     //resizes the map and adds default Tile()

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileTextureSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURE SHEET::FILENAME: " << texture_file << "\n";

		//Load all tiles
		while (in_file >> x >> y >> z >> type)
		{
			int enemy_type = 0;
			int enemy_amount = 0;
			int enemy_time_to_spawn = 0;
			int enemy_max_distance = 0;

			if (type == TileTypes::ENEMYSPAWNER)
			{
				in_file >> trX >> trY >> enemy_type >> enemy_amount >> enemy_time_to_spawn >> enemy_max_distance;

				this->map[x][y][z].push_back(
					new EnemySpawnerTile(
						x, y,
						gridSizeF,
						this->tileTextureSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
						enemy_type,
						enemy_amount,
						enemy_time_to_spawn,
						static_cast<float>(enemy_max_distance)
					)
				);
			}
			else
			{
				in_file >> trX >> trY >> collision;

				this->map[x][y][z].push_back(
					new RegularTile(
						type,
						x, y,
						gridSizeF,
						this->tileTextureSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
						collision
					)
				);
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	/* Take tbree indices from the mouse position on the grid and add a tile to that position if the internal tilemap array alows it*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0 )	
	{
		/*Can add a tile*/
		this->map[x][y][z].push_back(new RegularTile(type, x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision));
	}
	else
	{
		std::cout << "OUT OF BOUNDS\n" << 
					"x : "<< x << "\n" << 
					"y: "<< y << "\n" << 
					"z : "<< z << "\n" << 
					"this->maxSizeWorldGrid.x : "<< this->maxSizeWorldGrid.x << "\n" <<
					"this->maxSizeWorldGrid.y : "<< this->maxSizeWorldGrid.y << "\n" <<
					"this->layers : "<< this->layers << "\n" ;
	}
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect,
	const int enemy_type, const int enemy_amount, const int enemy_time_to_spawn, const int enemy_max_distance
	)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		this->map[x][y][z].push_back(new EnemySpawnerTile(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, enemy_type, enemy_amount, enemy_time_to_spawn, enemy_max_distance));
	}
}

void TileMap::removeTile(const int x, const int y, const int z, const int type)
{
	/* Take tbree indices from the mouse position on the grid and remove a tile to that position if the internal tilemap array alows it*/


	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			/* Can remove a tile
				!! SET IT TO NULL BECAUSE TILEMAP::ADDTILE WANTS NULL TO ADD A NEW TILE
			*/
			if (type >= 0)
			{
				if (this->map[x][y][z].back()->getType() == type)
				{
					delete this->map[x][y][z][this->map[x][y][z].size() - 1];
					this->map[x][y][z].pop_back();
				}
			}
			else
			{
				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				this->map[x][y][z].pop_back();
			}
		}
	}
}

const bool TileMap::checkType(const int x, const int y, const int type) const
{
	return this->map[x][y][this->layer].back()->getType() == type;
}

void TileMap::updateWorldBoundsCollision(Entity* entity, const float& dt)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > maxSizeWorldF.x)
	{
		entity->setPosition(maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
}

void TileMap::updateTileCollision(Entity* entity, const float& dt)
{
	//TILES
	this->layer = 0;
	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.x)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.x)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				this->map[x][y][this->layer][k]->Update();

				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (this->map[x][y][this->layer][k]->getCollision() &&
					this->map[x][y][this->layer][k]->intersects(nextPositionBounds)
					)
				{
					//Bottom Collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//Top Collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right Collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left Collision
					if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem)
{
	//TILES
	this->layer = 0;
	this->fromX = entity->getGridPosition(this->gridSizeI).x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.x)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 10;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.x)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				//Update the tile
				this->map[x][y][this->layer][k]->Update();

				//Update tile types (specific)
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER)
				{
					EnemySpawnerTile* es = dynamic_cast<EnemySpawnerTile*>(this->map[x][y][this->layer][k]);     //!!HAS TO BE POINTER TO BE ABLE TO DYNAMIC CAST
					if (es)
					{
						if (!es->getSpawned() && es->getEnemyCounter() < es->getEnemyAmount())
						{
							enemySystem.createEnemy(RAT, x * this->gridSizeF, y * this->gridSizeF, *es);
							es->setSpawned(true);
						}	
					}
				}
			}
		}
	}
}

void TileMap::Update(Entity* entity, const float& dt)
{
	

	
}

void TileMap::Render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, sf::Shader* shader, sf::Vector2f playerPosition, const bool show_collision)
{
	this->layer = 0;

	this->fromX = gridPosition.x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = gridPosition.x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = gridPosition.y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = gridPosition.y + 10;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::DOODAD)
				{
					this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
				}
				else
				{
					if (shader)
						this->map[x][y][this->layer][k]->Render(target, shader, playerPosition);

					else
						this->map[x][y][this->layer][k]->Render(target);
				}

				if (show_collision) 
				{
					if (this->map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}

				if (this->map[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER)
				{
					this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
					target.draw(this->collisionBox);
				}
			}
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
	while (!this->deferredRenderStack.empty())
	{
		if (shader)
			deferredRenderStack.top()->Render(target, shader, playerPosition);
		else
			deferredRenderStack.top()->Render(target);

		deferredRenderStack.pop();
	}
}