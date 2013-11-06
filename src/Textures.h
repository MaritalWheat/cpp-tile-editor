#pragma once
#include "stdafx.h"
#include <memory>

class Textures {
public:
	Textures();
	~Textures();
	static bool Initialize();
	static void TakeDown();
	void Add(std::string key, const std::string filename);
	void Remove(sf::Texture);
	void InitialLoad();
	static sf::Texture& Get(std::string name);

private:
	std::map<std::string, std::unique_ptr<sf::Texture>> _textureList;
	std::string _relativePath;
	static bool _initialized;
	static Textures *_textures;
};
