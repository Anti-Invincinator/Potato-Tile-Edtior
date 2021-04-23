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
	Tile(short type,
		int x, int y,
		float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		const bool collision
		);
	virtual ~Tile();

	//Accessors
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const std::string getAsString() const = 0;
	const short& getType() const;
	virtual const bool& getCollision() const;

	//Functions
	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_position = sf::Vector2f()) = 0;
};

#endif // !TILE_H