#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT = 0, DAMAGING, DOODAD};

class Tile
{
private:

protected:
	sf::Sprite shape;
	bool collision;
	short type;
	
public:
	//Constructor/Destructor
	Tile();
	Tile(int x, int y, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	//Accessors
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const std::string getAsString() const;
	const short& getType() const;

	//Functions
	const bool intersects(const sf::FloatRect bounds) const;
	void Update();
	void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());
};

#endif // !TILE_H