#ifndef REGULARTILE_H
#define REGULARTILE_H

#include "Tile.h"

class RegularTile :
	public Tile
{
private:

public:

	//Constructor / Destructor
	RegularTile(short type,
		int grid_x, int grid_y,
		float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false);

	virtual ~RegularTile();

	//Accessors
	virtual const std::string getAsString() const;

	//Functions
	virtual void Update();
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_position = sf::Vector2f());
};

#endif //!REGULARTILE_H


