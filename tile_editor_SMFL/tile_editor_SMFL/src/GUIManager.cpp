#include "stdafx.h"
#include "GUIManager.h"

GUIManager::GUIManager()
{
}

GUIManager::~GUIManager()
{
	std::for_each(_components.begin(),_components.end(),GameObjectDeallocator());
}

void GUIManager::Add(std::string name, GUIComponent* gameObject)
{
	_components.insert(std::pair<std::string,GUIComponent*>(name,gameObject));
}

void GUIManager::Remove(std::string name)
{
	std::map<std::string, GUIComponent*>::iterator results = _components.find(name);
	if(results != _components.end() )
	{
		delete results->second;
		_components.erase(results);
	}
}

GUIComponent* GUIManager::Get(std::string name) const
{
	std::map<std::string, GUIComponent*>::const_iterator results = _components.find(name);
	if(results == _components.end() )
		return NULL;
	return results->second;
	
}

int GUIManager::GetObjectCount() const
{
	return _components.size();
}


void GUIManager::DrawAll(sf::RenderWindow& renderWindow)
{

	std::map<std::string,GUIComponent*>::const_iterator itr = _components.begin();
	while(itr != _components.end())
	{
		renderWindow.draw(itr->second->GetSprite());
		itr++;
	}
}

void GUIManager::Contains(sf::Vector2<float> pos)
{
	std::map<std::string,GUIComponent*>::const_iterator itr = _components.begin();
	//float timeDelta = clock.restart().asSeconds();

	while(itr != _components.end())
	{
		if(itr->second->Contains(pos)) {
			itr->second->SetColor(sf::Color::Red);
		} else {
			itr->second->SetColor(sf::Color::Green);
		}
		itr++;
	}

	
}