#pragma once
#include "stdafx.h"

class GUIComponent {
public:
	
	enum Type {
		_button,
		_box,
		_toggle
	};
	GUIComponent();
	GUIComponent(sf::Texture& texture, GUIComponent::Type);
	GUIComponent(sf::Texture &normal, sf::Texture &hover, GUIComponent::Type);
	GUIComponent(sf::Texture &normal, sf::Texture &hover, sf::Texture &clicked, GUIComponent::Type);
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
	sf::Text GetText();
	GUIComponent::Type GetType();
	bool IsClicked();
	void SetClicked(bool status);
	void SetTexture(sf::Texture &texture);
	void SetText(std::string str);
	sf::Texture _normal;
	sf::Texture _hover;
	sf::Texture _clicked;
private: 
	sf::Sprite _sprite;
	sf::Text _text;
	sf::Font _font;
	GUIComponent::Type _type;
	bool _isClicked;
	void UpdateTextPosition();
};