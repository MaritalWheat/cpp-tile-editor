#pragma once
#include "stdafx.h"

class Textures {
public:
	Textures();
	~Textures();
	static bool Initialize();
	static void TakeDown();
	void Add(std::string key, sf::Texture texture);
	void Remove(sf::Texture);
	void InitialLoad();
	static sf::Texture Get(std::string name);

private:
	std::map<std::string, sf::Texture> _textureList;
	std::string _relativePath;
	static bool _initialized;
	static Textures *_textures;
};
