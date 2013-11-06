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

void Textures::Add(std::string key, const std::string filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if(!texture->loadFromFile(filename))
    {
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }
	auto inserted = _textureList.insert(std::make_pair(key, std::move(texture)));
    assert(inserted.second);
}

sf::Texture& Textures::Get(std::string name) {
	auto results = _textures->_textureList.find(name);
	if(results == _textures->_textureList.end()) {
#ifdef _DEBUG
		printf("Error: texture not found!");
#endif
		//return sf::Texture(); //handle no texture found
	}
	return *(results)->second;
}

//naming conventions: _a = active, _h = hover, _n = normal
void Textures::InitialLoad() {
	Add("Button", _relativePath + "Assets/button_normal.png");

	Add("Button_h", _relativePath + "Assets/button_hover.png");	

	Add("R_Arrow", _relativePath + "Assets/right_arrow.png");

	Add("R_Arrow_h", _relativePath + "Assets/right_arrow_hover.png");

	Add("L_Arrow", _relativePath + "Assets/left_arrow.png");

	Add("L_Arrow_h", _relativePath + "Assets/left_arrow_hover.png");

	Add("Box", _relativePath + "Assets/guibox.png");

	Add("Box_Dark", _relativePath + "Assets/box_dark.png");

	Add("Box_Small", _relativePath + "Assets/small_box.png");

	Add("Box_Small_a", _relativePath + "Assets/small_box_clicked.png");
}

