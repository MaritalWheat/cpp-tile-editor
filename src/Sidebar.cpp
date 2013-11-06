#include "Sidebar.h"

Sidebar::Sidebar() {
}

Sidebar::Sidebar(sf::RenderWindow &window, GUIComponent *topBar) {
	_sidebar = new GUIManager();
	InitialLoad(window, topBar);
}

Sidebar::~Sidebar() {
	delete _sidebar;
}

void Sidebar::Draw(sf::RenderWindow &window) {
	_sidebar->DrawAll(window);
}

void Sidebar::InitialLoad(sf::RenderWindow &window, GUIComponent *topBar) {
	
	_background = new GUIComponent(Textures::Get("Box"), GUIComponent::Type::_box);
	_background->SetScale(32 * 6 / _background->GetWidth(), 32 * 23 / _background->GetHeight());
	_background->SetPosition(window.getSize().x - _background->GetWidth(), topBar->GetY() + topBar->GetHeight());
	_sidebar->Add("Background", _background);

	_header = new GUIComponent(Textures::Get("Box_Dark"), GUIComponent::Type::_box);
	_header->SetScale(32 * 6 / _header->GetWidth(), 32 / _header->GetHeight());
	_header->SetPosition(window.getSize().x - _header->GetWidth(), 0);
	_sidebar->Add("Header", _header);

	/*sf::Vector2f tileTypeButtonScale = sf::Vector2f(32 * 4 / _header->GetWidth(), 32 * 1 / grassOption->GetHeight());
	sf::Vector2f tileTypeButtonPos = sf::Vector2f(_header->GetX() + 32, _header->GetY());

	GUIComponent *optionsListRight = new GUIComponent(Textures::Get("R_Arrow"), Textures::Get("R_Arrow_h"), GUIComponent::Type::_button);
	GUIComponent *optionsListLeft = new GUIComponent(Textures::Get("L_Arrow"), Textures::Get("L_Arrow_h"), GUIComponent::Type::_button);

	optionsListRight -> SetScale(32 / optionsListRight->GetWidth(), tileTypeButtonScale.y);
	optionsListRight -> SetPosition(button2->GetX() + button2->GetWidth() - optionsListRight->GetWidth(), button2->GetY());

	optionsListLeft -> SetScale(32 / optionsListLeft->GetWidth(), tileTypeButtonScale.y);
	optionsListLeft -> SetPosition(button2->GetX(), button2->GetY());*/
}

