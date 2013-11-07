#include "Sidebar.h"

Sidebar::Sidebar() {
}

Sidebar::Sidebar(sf::RenderWindow &window, GUIComponent *topBar) {
	_selectedType = nullptr;
	_sidebar = new GUIManager();
	LoadTiles();
	InitialLoad(window, topBar);
}

Sidebar::~Sidebar() {
	delete _sidebar;
	for (int i = 0; i < _tileTypes.size(); i++) {
		delete _tileTypes[i];
	}
	_tileTypes.clear();
}

void Sidebar::Draw(sf::RenderWindow &window) {
	_sidebar->DrawAll(window);
}

bool Sidebar::Contains(sf::Vector2<float> pos) {
	if (_selectedType != _sidebar->_lastSelected) {
		if (_selectedType != nullptr) {
			_selectedType->SetClicked(false); //clear old selected
		}

		if (_sidebar->_lastSelected != nullptr) {
			_selectedType = _sidebar->_lastSelected; //set new selected
		}
	}
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
	_header->SetText("Tile Type");
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

	for (int i = 0; i < 11; i++) {
		GUIComponent* option(new GUIComponent(Textures::Get("Button"), GUIComponent::Type::_box));
		GUIComponent* checkBox(new GUIComponent(Textures::Get("Box_Small"), Textures::Get("Box_Small"), Textures::Get("Box_Small_a"), GUIComponent::Type::_toggle));
	
		if (i < _tileTypes.size()) {
			option->SetText(_tileTypes[i]->GetType());
		} else {
			option->SetText("Option");
		}

		tileTypeButtonPos.y += 64;
		option->SetScale((_header->GetWidth() - (_arrowRight->GetWidth() * 2)) / option->GetWidth(), tileTypeButtonScale.y);
		option->SetPosition(tileTypeButtonPos.x, tileTypeButtonPos.y);
		checkBox->SetScale(32 / checkBox->GetWidth(), 32 / checkBox->GetHeight());
		checkBox->SetPosition(tileTypeButtonPos.x + 32 * 3, tileTypeButtonPos.y);	

		std::string key = "Option ";
		key.append(std::to_string(i));
		_sidebar->Add(key, option);
		key = "Box ";
		key.append(std::to_string(i));
		_sidebar->Add(key, checkBox);
	}
}	

void Sidebar::LoadTiles() {
	_tileTypes.push_back(new Tile("Grass"));
}

	

