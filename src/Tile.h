#pragma once
#include "stdafx.h"


class Tile
{
public:
  Tile();
  Tile(sf::Texture& texture);
  ~Tile();
  float GetHeight();
  float GetWidth();
  float GetX();
  float GetY();
  void SetPosition(float x, float y);
  sf::Sprite GetSprite();

private:
	sf::Sprite _sprite;
};