#pragma once
#include "stdafx.h"
#include "GUIComponent.h"
#include "GUIManager.h"
#include "Textures.h"
#include "Tile.h"
#include <vector>

class Sidebar {
public:
	Sidebar();
	Sidebar(sf::RenderWindow &window, GUIComponent *topBar);
	~Sidebar();
	void Draw(sf::RenderWindow &window);
	void InitialLoad(sf::RenderWindow &window, GUIComponent *topBar);
	void LoadTiles();
	bool Contains(sf::Vector2<float> pos);
	GUIComponent* _selectedType;

protected:
	GUIManager* _sidebar;
	GUIComponent* _header;
	GUIComponent* _background;
	GUIComponent* _arrowLeft;
	GUIComponent* _arrowRight;
	std::vector<Tile*> _tileTypes;
};