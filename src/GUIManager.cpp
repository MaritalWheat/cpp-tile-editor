#include "stdafx.h"
#include "GUIManager.h"

GUIManager::GUIManager()
{
}

GUIManager::~GUIManager()
{
	std::for_each(_components.begin(),_components.end(), GameObjectDeallocator());
}

void GUIManager::Add(std::string name, GUIComponent* gameObject)
{
	_components.insert(std::pair<std::string,GUIComponent*>(name,gameObject));
	_drawOrderedComponents.push_back(name);
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
	std::vector<std::string>::const_iterator itr = _drawOrderedComponents.begin();
	while(itr != _drawOrderedComponents.end())
	{
		std::string key = *itr;
		renderWindow.draw(_components.find(key)->second->GetSprite());
		itr++;
	}
}

bool GUIManager::Contains(sf::Vector2<float> pos)
{
	bool mouseInGUI = false;
	std::map<std::string,GUIComponent*>::const_iterator itr = _components.begin();
	//float timeDelta = clock.restart().asSeconds();

	while(itr != _components.end())
	{
		if (itr->second->GetType() == GUIComponent::Type::_button) {
			//printf("" + (itr -> second -> IsClicked()));
			if(itr->second->Contains(pos)) {
				mouseInGUI = true;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					itr->second->SetClicked(!itr->second->IsClicked());
					itr->second->SetTexture(itr->second->_clicked);
				} else {
					itr->second->SetTexture(itr->second->_hover);
				}
			} else if (itr->second->IsClicked()) {
				itr->second->SetTexture(itr->second->_clicked);
			} else {
				itr->second->SetTexture(itr->second->_normal);
			}
		} else if (itr->second->GetType() == GUIComponent::Type::_toggle) {
			if(itr->second->Contains(pos)) {
				mouseInGUI = true;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					itr->second->SetClicked(!itr->second->IsClicked());
					//itr->second->SetTexture(itr->second->_clicked);
				}
			}
			
			if (itr->second->IsClicked()) {
				itr->second->SetTexture(itr->second->_clicked);
			} else {
				itr->second->SetTexture(itr->second->_normal);
			}
		} else if (itr->second->GetType() == GUIComponent::Type::_box) {
			itr->second->SetTexture(itr->second->_normal); //strange that this needs to be set, but otherwise box type gets wrong texture
			if(itr->second->Contains(pos)) {
				mouseInGUI = true;
			}
		}
		itr++;
	}
	return mouseInGUI;
	
}