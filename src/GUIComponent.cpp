#include "GUIComponent.h"

GUIComponent::GUIComponent() 
{
}

GUIComponent::GUIComponent(sf::Texture &texture, GUIComponent::Type type) 
{
	_type = type;
	_isClicked = false;
	_normal = _hover = _clicked = texture;
	this->SetTexture(_normal);
}

GUIComponent::GUIComponent(sf::Texture &normal, sf::Texture &hover, GUIComponent::Type type) 
{
	_sprite = sf::Sprite(normal);
	_type = type;
	_isClicked = false;
	_normal = normal;
	_hover = _clicked = hover;
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
	UpdateTextPosition();
}

void GUIComponent::SetScale(float x, float y) 
{
	_sprite.setScale(x, y);
	UpdateTextPosition();
}

void GUIComponent::SetColor(sf::Color color)
{
	_sprite.setColor(color);
}

sf::Sprite GUIComponent::GetSprite()
{
	return _sprite;
}

sf::Text GUIComponent::GetText()
{
	return _text;
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

void GUIComponent::SetText(std::string str)
{
	_font.loadFromFile("C:/Users/Emanuel/Documents/Visual Studio 2012/Projects/ConsoleApplication1/Assets/BebasNeue.otf");
	_text.setFont(_font);
	_text.setString(str);
	//_text.setStyle(sf::Text::Bold);
	_text.setColor(sf::Color::White);
	UpdateTextPosition();
}

void GUIComponent::UpdateTextPosition()
{
	_text.setCharacterSize(this->GetHeight() / 1.5);
	_text.setPosition((this->GetX() + this->GetWidth() / 2 - _text.getLocalBounds().width / 2), this->GetY() + (this->GetHeight() / 2) -
		(_text.getLocalBounds().height / 2) - 5);
}


