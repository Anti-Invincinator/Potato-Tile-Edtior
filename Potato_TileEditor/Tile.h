#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT_TILE = 0, DAMAGING, DOODAD, ENEMYSPAWNER};

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
		bool collision = false, short type = TileTypes::DEFAULT_TILE);
	virtual ~Tile();

	//Accessors
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const std::string getAsString() const;
	const short& getType() const;

	//Functions
	const bool intersects(const sf::FloatRect bounds) const;
	virtual void Update();
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_position = sf::Vector2f());
};

#endif // !TILE_H