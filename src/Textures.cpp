#include "Textures.h"

bool Textures::_initialized;
Textures* Textures::_textures;

Textures::Textures() {
	_relativePath = "C:/Users/Emanuel/Documents/Visual Studio 2012/Projects/ConsoleApplication1/";
	InitialLoad();
}

Textures::~Textures() {
	_textureList.clear();
}

bool Textures::Initialize() {
	assert(!_initialized); //sanity check
	_textures = new Textures();
	_initialized = true;
	return _initialized;
}

void Textures::TakeDown() {
	assert(_initialized);
	delete _textures;
}

void Textures::Add(std::string key, sf::Texture texture) {
	_textureList.insert(std::pair<std::string, sf::Texture>(key, texture));
}

sf::Texture Textures::Get(std::string name) {
	std::map<std::string, sf::Texture>::const_iterator results = _textures->_textureList.find(name);
	if(results == _textures->_textureList.end()) {
#ifdef _DEBUG
		printf("Error: texture not found!");
#endif
		return sf::Texture(); //handle no texture found
	}
	return results->second;
}

//naming conventions: _a = active, _h = hover, _n = normal
void Textures::InitialLoad() {
	sf::Texture texButton;
	texButton.loadFromFile(_relativePath + "Assets/button_normal.png");
	Add("Button", texButton);

	sf::Texture texButtonHover;
	texButtonHover.loadFromFile(_relativePath + "Assets/button_hover.png");
	Add("Button_h", texButtonHover);	

	sf::Texture texArrowRight;
	texArrowRight.loadFromFile(_relativePath + "Assets/right_arrow.png");
	Add("R_Arrow", texArrowRight);

	sf::Texture texArrowRightHover;
	texArrowRightHover.loadFromFile(_relativePath + "Assets/right_arrow_hover.png");
	Add("R_Arrow_h", texArrowRightHover);

	sf::Texture texArrowLeft;
	texArrowLeft.loadFromFile(_relativePath + "Assets/left_arrow.png");
	Add("L_Arrow", texArrowLeft);

	sf::Texture texArrowLeftHover;
	texArrowLeftHover.loadFromFile(_relativePath + "Assets/left_arrow_hover.png");
	Add("L_Arrow_h", texArrowLeftHover);

	sf::Texture texGUIBack;
	texGUIBack.loadFromFile(_relativePath + "Assets/guibox.png");
	Add("Box", texGUIBack);

	sf::Texture texGUIBackDark;
	texGUIBackDark.loadFromFile(_relativePath + "Assets/box_dark.png");
	Add("Box_Dark", texGUIBackDark);

	sf::Texture texSmallBox;
	texSmallBox.loadFromFile(_relativePath + "Assets/small_box.png");
	Add("Box_Small", texSmallBox);

	sf::Texture texSmallBoxClicked;
	texSmallBoxClicked.loadFromFile(_relativePath + "Assets/small_box_clicked.png");
	Add("Box_Small_a", texSmallBoxClicked);
}

