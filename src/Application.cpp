#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Textures.h"
#include "Sidebar.h"
#include "GUIComponent.h"
#include "GUIManager.h"
#include <vector>
#include <stdio.h>
#include "vld.h"

int main()
{
	Textures::Initialize();

	std::string str;
	std::string _relativePath = "C:/Users/Emanuel/Documents/Visual Studio 2012/Projects/ConsoleApplication1/";
	sf::String startText;
	sf::Font _font;
	_font.loadFromFile(_relativePath + "Assets/BebasNeue.otf");

	sf::RenderWindow window(sf::VideoMode(1024, 756), "Using sf::View", sf::Style::Close | sf::Style::Titlebar); // Create window
	window.setFramerateLimit(60); // Set a framerate limit to reduce the CPU load
	window.setMouseCursorVisible(false); // Hide the cursor

	sf::Texture texMap; // Create the world startTexture and sprite
	texMap.setSmooth(true);
	texMap.loadFromFile(_relativePath + "Assets/world.png");
	sf::Sprite map(texMap);
	
	sf::Texture texTile;
	texTile.loadFromFile(_relativePath + "Assets/EmptyTile.png");

	sf::Texture texWaterTile;
	texWaterTile.loadFromFile(_relativePath + "Assets/Water.png");

	sf::Texture texGrassTile;
	texGrassTile.loadFromFile(_relativePath + "Assets/Grass.png");

	sf::Texture texPlacerTile;
	//texPlacerTile.loadFromFile(_relativePath + "Assets/Grass.png");
	texPlacerTile = texGrassTile;

	sf::Texture texHighlightTile;
	texHighlightTile.loadFromFile(_relativePath + "Assets/TileTest.png");

	GUIManager *_gui = new GUIManager();
	Tile *testTile = new Tile(texHighlightTile);

	GUIComponent *topBar = new GUIComponent(Textures::Get("Box"), GUIComponent::Type::_box);

	GUIComponent *button1 = new GUIComponent(Textures::Get("Box_Dark"), GUIComponent::Type::_toggle);

	topBar -> SetScale(window.getSize().x / topBar->GetWidth(), 32 / button1 -> GetHeight()); 
	button1 -> SetScale(32 * 5 / button1->GetWidth(), 32 / button1 -> GetHeight()); 
	
	topBar -> SetPosition(0, 0);
	button1 -> SetPosition(0, 0);

	Sidebar *sidebar = new Sidebar(window, topBar);
	
	_gui->Add("c", topBar);
	_gui->Add("b", button1);

	const int _mapWidth = (int)map.getLocalBounds().width / 32;
	const int _mapHeight = (int)map.getLocalBounds().height / 32;

	std::vector<std::vector<Tile>> tileMap;
	tileMap.resize(_mapWidth);
	for(unsigned int i = 0; i < tileMap.size(); ++i) {
		tileMap[i].resize(_mapHeight);
	}

	for(unsigned int i = 0; i < tileMap.size(); ++i) {
		for (unsigned int j = 0; j < tileMap[i].size(); ++j) {
			std::auto_ptr<Tile> tmp(new Tile(texTile));
			tileMap[i][j] = *tmp;
			tileMap[i][j].SetPosition(map.getGlobalBounds().left + i * 32, map.getGlobalBounds().top + j * 32);
		}
	}

	
	std::vector<Tile> _placedTiles;
	int _size = 0;
	_placedTiles.resize(0);


	sf::Texture texLink; // Create the link startTexture and sprite which will be out cursor
	texLink.loadFromFile(_relativePath + "Assets/link.png");
	sf::Sprite link(texLink);
	link.setOrigin(8.f, 8.f); // The cursors point should be in the middle
	float _cameraPosX = 0.0f;
	float _cameraPosY = 0.0f;
	
	
	sf::View fixed = window.getView(); // The 'fixed' view will never change

	sf::View standard = fixed; // The 'standard' view will be the one that gets always displayed
	link.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));

	sf::Vector2i pos = sf::Mouse::getPosition(); // We will keep track of the old mouse position

	bool moved = true; // Did the views move?
	std::stringstream ss; // Used to convert integers and floats to strings

	while(window.isOpen()) // As long as the window is open
	{
		sf::Event event; // Normal event handling

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed) {
				delete sidebar;
				delete _gui;
				delete testTile;
				tileMap.clear();
				//_placedTiles._Destroy();
				Textures::TakeDown();
				window.close();
				exit(0);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if(_cameraPosX > map.getPosition().x + 3) {
				standard.move(-3.f, 0.f);
				_cameraPosX -= 3;
			} else {
				link.setPosition(link.getPosition().x - 3, link.getPosition().y);
				_cameraPosX -= 3;
			}
			moved = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (_cameraPosX > map.getPosition().x) {
				standard.move(3.f, 0.f);
			} else { 
				link.setPosition(link.getPosition().x + 3, link.getPosition().y);
			}
			_cameraPosX += 3;
			moved = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (_cameraPosY > map.getPosition().y + 3) {
				standard.move(0.0f, -3.0f);
			} else { 
				link.setPosition(link.getPosition().x, link.getPosition().y - 3);
			}
			_cameraPosY -= 3;
			moved = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (_cameraPosY <= map.getPosition().y + map.getGlobalBounds().height - window.getSize().y + 10) {
				standard.move(0.0f, 3.0f);
			} else { 
				link.setPosition(link.getPosition().x, link.getPosition().y + 3);
			}
			_cameraPosY += 3;
			moved = true;
		}


		if(moved || pos != sf::Mouse::getPosition(window)) // Views got moved or the mouse got moved
		{
			pos = sf::Mouse::getPosition(window); // Get the new position
			float x = window.mapPixelToCoords(pos, standard).x;
			float y = window.mapPixelToCoords(pos, standard).y;
			int i = (int)(x / 32);
			int j = (int)(y / 32);

			if (pos.x < window.getSize().x && pos.y < window.getSize().y) { //why the fuck does this work??
				float x = tileMap[i][j].GetX();
				float y = tileMap[i][j].GetY();
				testTile->SetPosition(x, y);
				button1->SetText(std::string("( ").append(std::to_string((int)(x / 32))).append(", ").append(std::to_string((int)(y / 32))).append(std::string(" )")));
				
				/*if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					++_size;
					_placedTiles.resize(_size);
					GUIComponent *currentlyClicked = new GUIComponent();
					if (grassCheckBox->IsClicked()) {
						Tile *tmp = new Tile(texGrassTile);
						_placedTiles[_size - 1] = *tmp;
						_placedTiles[_size - 1].SetPosition(tileMap[i][j].GetX(), tileMap[i][j].GetY());
						if (grassCheckBox != currentlyClicked) {
							currentlyClicked->SetClicked(false);
							currentlyClicked = grassCheckBox;
						}
					}
					if (waterOption->IsClicked()) {
						Tile *tmp = new Tile(texWaterTile);
						_placedTiles[_size - 1] = *tmp;
						_placedTiles[_size - 1].SetPosition(tileMap[i][j].GetX(), tileMap[i][j].GetY());
						if (waterOption != currentlyClicked) {
							currentlyClicked->SetClicked(false);
							currentlyClicked = waterOption;
						}
					}
				}*/
			}
			//printf("Test.\n");
			bool mouseVis = false;
			if(_gui->Contains((sf::Vector2<float>)(pos))) {
				mouseVis = true;
			}
			if (sidebar->Contains((sf::Vector2<float>)(pos))) {
				mouseVis = true;
			}
			if (mouseVis) {
				window.setMouseCursorVisible(true);
			} else {
				window.setMouseCursorVisible(false);
			}

			
		}

		window.clear(); // Remove old content

		window.setView(standard);


		for(unsigned int i = 0; i < tileMap.size(); ++i) {
			for (unsigned int j = 0; j < tileMap[i].size(); ++j) {
				window.draw(tileMap[i][j].GetSprite());
			}
		}
		for(int i = 0; i < _size; ++i) {
			window.draw(_placedTiles[i].GetSprite());
		}
		window.draw(testTile->GetSprite());


		window.setView(fixed);

		_gui->DrawAll(window);
		sidebar->Draw(window);

		window.draw(link);


		window.display(); // Show everything
	}
	}
	return 0;
}

