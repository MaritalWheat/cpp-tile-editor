#include "StdAfx.h"
#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(sf::Texture& texture) 
{
	_sprite = sf::Sprite(texture);
}

Tile::Tile(std::string type) 
{
	_type = type;
	_sprite = sf::Sprite(Textures::Get(_type));
}

Tile::~Tile()
{
}

float Tile::GetHeight()
{
	return _sprite.getGlobalBounds().height;
}

float Tile::GetWidth()
{
	return _sprite.getGlobalBounds().width;
}

float Tile::GetX()
{
	return _sprite.getPosition().x;
}

float Tile::GetY() 
{
	return _sprite.getPosition().y;
}

void Tile::SetPosition(float x, float y) 
{
	_sprite.setPosition(x, y);
}

sf::Sprite Tile::GetSprite()
{
	return _sprite;
}

std::string Tile::GetType() {
	return _type;
}
