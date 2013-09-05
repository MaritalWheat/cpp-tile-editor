#pragma once
#include "GUIComponent.h"


class GUIManager
{
public:	
	GUIManager();
	~GUIManager();

	void Add(std::string name, GUIComponent* guiComponent);
	void Remove(std::string name);
	int GetObjectCount() const;
	GUIComponent* Get(std::string name) const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void Contains(sf::Vector2<float> pos);

private:
	std::map<std::string, GUIComponent*> _components;

	sf::Clock clock;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string,GUIComponent*> & p) const
		{
			delete p.second;
		}
	};
};