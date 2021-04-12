#include "stdafx.h"
#include "TileMap.h"

void TileMap::Clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

//Constructor / Destructor
TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	//use reserve not resize  (for push_back)
	//if using resize (size, default value) and remove the push back function  !!!!!Resize resizes the internal array and adds default values

	this->map.resize(this->maxSize.x, std::vector< std::vector< Tile* > >());     //resizes the map and adds default Tile()

	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}

	if (!this->tileTextureSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURE SHEET::FILENAME: "<<texture_file << "\n";
}

TileMap::~TileMap()
{
	this->Clear();
}

//Accessors
const sf::Texture* TileMap::getTileTextureSheet() const
{
	return &this->tileTextureSheet;
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
	gridPos x y layer(of all tiles), Texture rect x y, collision, type
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		//Iterate through each induvidual tile
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
					out_file << x << " " << y << " " << z << " " << 
						this->map[x][y][z]->getAsString()
						<< "\n";													 //MAKE SURE THE LAST SPACE IS NOT SAVED TO PREVENT ISSUES from getline(), cin
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
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;


		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->Clear();

		//use reserve not resize  (for push_back)
		//if using resize (size, default value) and remove the push back function  !!!!!Resize resizes the internal array and adds default values

		this->map.resize(this->maxSize.x, std::vector< std::vector< Tile* > >());     //resizes the map and adds default Tile()

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, nullptr);
				}
			}
		}

		if (!this->tileTextureSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURE SHEET::FILENAME: " << texture_file << "\n";

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(
				x, y, gridSizeF,
				this->tileTextureSheet, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				collision, type
			);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	/* Take tbree indices from the mouse position on the grid and add a tile to that position if the internal tilemap array alows it*/

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0 )	
	{
		if (this->map[x][y][z] == nullptr)
		{
			/*Can add a tile*/
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision, type);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/* Take tbree indices from the mouse position on the grid and remove a tile to that position if the internal tilemap array alows it*/


	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			/* Can remove a tile
				!! SET IT TO NULL BECAUSE TILEMAP::ADDTILE WANTS NULL TO ADD A NEW TILE
			*/
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
		}
	}
}

void TileMap::Update()
{

}

void TileMap::Render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if(z != nullptr)
				z->Render(target);
			}
		}
	}
}



