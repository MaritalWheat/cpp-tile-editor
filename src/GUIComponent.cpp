#include "GUIComponent.h"

GUIComponent::GUIComponent() 
{
}

GUIComponent::GUIComponent(sf::Texture& texture, GUIComponent::Type type) 
{
	_sprite = sf::Sprite(texture);
	_type = type;
	_isClicked = false;
	_normal = _hover = _clicked = texture;
}

GUIComponent::GUIComponent(sf::Texture &normal, sf::Texture &hover, GUIComponent::Type type) 
{
	_sprite = sf::Sprite(normal);
	_type = type;
	_isClicked = false;
	_normal = _hover = _clicked = normal;
	_hover = hover;
}

GUIComponent::GUIComponent(sf::Texture &normal, sf::Texture &hover, sf::Texture &clicked, GUIComponent::Type type) 
{
	_sprite = sf::Sprite(normal);
	_type = type;
	_isClicked = false;
	_normal = normal;
	_hover = hover;
	_clicked = clicked;
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

GUIComponent::Type GUIComponent::GetType()
{
	return _type;
}

bool GUIComponent::IsClicked()
{
	return _isClicked;
}

void GUIComponent::SetClicked(bool status) 
{
	_isClicked = status;
}

void GUIComponent::SetTexture(sf::Texture &texture)
{
	_sprite.setTexture(texture);
}


