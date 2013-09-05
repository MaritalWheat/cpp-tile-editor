#include "GUIComponent.h"

GUIComponent::GUIComponent() 
{
}

GUIComponent::GUIComponent(sf::Texture& texture) 
{
	_sprite = sf::Sprite(texture);
}

GUIComponent::~GUIComponent()
{
}

float GUIComponent::GetHeight()
{
	return _sprite.getGlobalBounds().height;
}

float GUIComponent::GetWidth() 
{
	return _sprite.getGlobalBounds().width;
}

float GUIComponent::GetX()
{
	return _sprite.getPosition().x;
}

float GUIComponent::GetY()
{
	return _sprite.getPosition().y;
}

bool GUIComponent::Contains(sf::Vector2<float> point)
{
	return _sprite.getGlobalBounds().contains(point);
}

sf::Vector2<float> GUIComponent::GetScale()
{
	return _sprite.getScale();
}

void GUIComponent::SetPosition(float x, float y) 
{
	_sprite.setPosition(x, y);
}

void GUIComponent::SetScale(float x, float y) 
{
	_sprite.setScale(x, y);
}

void GUIComponent::SetColor(sf::Color color)
{
	_sprite.setColor(color);
}

sf::Sprite GUIComponent::GetSprite()
{
	return _sprite;
}


