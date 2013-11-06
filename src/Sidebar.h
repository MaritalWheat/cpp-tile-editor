#pragma once
#include "stdafx.h"
#include "GUIComponent.h"
#include "GUIManager.h"
#include "Textures.h"
#include <vector>

class Sidebar {
public:
	Sidebar();
	Sidebar(sf::RenderWindow &window, GUIComponent *topBar);
	~Sidebar();
	void Draw(sf::RenderWindow &window);
	void InitialLoad(sf::RenderWindow &window, GUIComponent *topBar);
	bool Contains(sf::Vector2<float> pos);
	GUIComponent* _header; //make this private after adding text function to guicomponents 

protected:
	GUIManager* _sidebar;
	GUIComponent* _background;
	GUIComponent* _arrowLeft;
	GUIComponent* _arrowRight;
};