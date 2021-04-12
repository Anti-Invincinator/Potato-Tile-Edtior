#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

//Constructor/Destructor
Tile::Tile(unsigned x, unsigned y, float gridSizeF,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{
}

//Accessors
const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

	return ss.str();
}

//Functions
void Tile::Update()
{
}

void Tile::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
