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

bool Sidebar::Contains(sf::Vector2<float> pos) {
	return _sidebar->Contains(pos);
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

	_arrowRight = new GUIComponent(Textures::Get("R_Arrow"), Textures::Get("R_Arrow_h"), GUIComponent::Type::_button);
	_arrowLeft = new GUIComponent(Textures::Get("L_Arrow"), Textures::Get("L_Arrow_h"), GUIComponent::Type::_button);

	sf::Vector2f tileTypeButtonScale = sf::Vector2f(32 * 4 / _header->GetWidth(), _header->GetHeight() / _arrowLeft->GetHeight());
	sf::Vector2f tileTypeButtonPos = sf::Vector2f(_header->GetX() + 32, _header->GetY());

	_arrowRight -> SetScale(32 / _arrowRight->GetWidth(), tileTypeButtonScale.y);
	_arrowRight -> SetPosition(_header->GetX() + _header->GetWidth() - _arrowRight->GetWidth(), _header->GetY());
	_sidebar->Add("Arrow_Right", _arrowRight);

	_arrowLeft -> SetScale(32 / _arrowLeft->GetWidth(), tileTypeButtonScale.y);
	_arrowLeft -> SetPosition(_header->GetX(), _header->GetY());
	_sidebar->Add("Arrow_Left", _arrowLeft);

	/*std::auto_ptr<GUIComponent> grassOption(new GUIComponent(Textures::Get("Button"), Textures::Get("Button_h"), GUIComponent::Type::_toggle));
	GUIComponent *waterOption = new GUIComponent(Textures::Get("Button"), Textures::Get("Button_h"), GUIComponent::Type::_toggle);
	GUIComponent *dirtOption = new GUIComponent(Textures::Get("Button"), Textures::Get("Button_h"), GUIComponent::Type::_toggle);
	GUIComponent *sandOption = new GUIComponent(Textures::Get("Button"), Textures::Get("Button_h"), GUIComponent::Type::_toggle);
	GUIComponent *deepWaterOption = new GUIComponent(Textures::Get("Button"), Textures::Get("Button_h"), GUIComponent::Type::_toggle);
	GUIComponent *grassOptionIcon = new GUIComponent(texGrassTile, Textures::Get("Button_h"), GUIComponent::Type::_box);
	GUIComponent *grassCheckBox = new GUIComponent(Textures::Get("Box_Small"), Textures::Get("Box_Small"), Textures::Get("Box_Small_a"), GUIComponent::Type::_toggle);*/
}	

	

