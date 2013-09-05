#pragma once
#include "stdafx.h"

class GUIComponent {
public:
	GUIComponent();
	GUIComponent(sf::Texture& texture);
	~GUIComponent();

	float GetHeight();
	float GetWidth();
	float GetX();
	float GetY();
	bool Contains(sf::Vector2<float>);
	sf::Vector2<float> GetScale();
	void SetPosition(float x, float y);
	void SetScale(float x, float y);
	void SetColor(sf::Color color);
	sf::Sprite GetSprite();
private: 
	sf::Sprite _sprite;
};