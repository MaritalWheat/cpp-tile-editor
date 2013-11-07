#pragma once
#include "stdafx.h"
#include "Textures.h"


class Tile
{
public:
  Tile();
  Tile(sf::Texture& texture);
  Tile(std::string type);
  ~Tile();
  float GetHeight();
  float GetWidth();
  float GetX();
  float GetY();
  void SetPosition(float x, float y);
  sf::Sprite GetSprite();
  std::string GetType();

private:
	sf::Sprite _sprite;
	std::string _type;
};