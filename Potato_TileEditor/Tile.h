#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;
	
public:
	//Constructor/Destructor
	Tile();
	Tile(unsigned x, unsigned y, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	//Accessors
	const std::string getAsString() const;
	const sf::Vector2f& getPosition() const;
	const bool getCollision() const;

	//Functions
	void Update();
	void Render(sf::RenderTarget& target);
};

#endif // !TILE_H



