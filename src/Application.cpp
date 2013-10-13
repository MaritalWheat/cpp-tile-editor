#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "GUIComponent.h"
#include "GUIManager.h"
#include <vector>
#include <stdio.h>

int main()
{
	std::string str;
	std::string _relativePath = "C:/Users/Emanuel/Documents/Visual Studio 2012/Projects/ConsoleApplication1/";
	sf::String startText;
	sf::Font _font;
	_font.loadFromFile(_relativePath + "Assets/BebasNeue.otf");

	sf::RenderWindow window(sf::VideoMode(1024, 756), "Using sf::View", sf::Style::Close | sf::Style::Titlebar); // Create window
	window.setFramerateLimit(60); // Set a framerate limit to reduce the CPU load
	window.setMouseCursorVisible(false); // Hide the cursor

	sf::Texture texButton;
	texButton.loadFromFile(_relativePath + "Assets/button_normal.png");

	sf::Texture texArrowRight;
	texArrowRight.loadFromFile(_relativePath + "Assets/right_arrow.png");

	sf::Texture texArrowRightHover;
	texArrowRightHover.loadFromFile(_relativePath + "Assets/right_arrow_hover.png");

	sf::Texture texArrowLeft;
	texArrowLeft.loadFromFile(_relativePath + "Assets/left_arrow.png");

	sf::Texture texArrowLeftHover;
	texArrowLeftHover.loadFromFile(_relativePath + "Assets/left_arrow_hover.png");

	sf::Texture texButtonHover;
	texButtonHover.loadFromFile(_relativePath + "Assets/button_hover.png");
	sf::Texture texGUIBack;

	texGUIBack.loadFromFile(_relativePath + "Assets/guibox.png");

	sf::Texture texGUIBackDark;
	texGUIBackDark.loadFromFile(_relativePath + "Assets/box_dark.png");

	sf::Texture texSmallBox;
	texSmallBox.loadFromFile(_relativePath + "Assets/small_box.png");

	sf::Texture texSmallBoxClicked;
	texSmallBoxClicked.loadFromFile(_relativePath + "Assets/small_box_clicked.png");

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
	Tile *tile1 = new Tile(texTile);
	Tile *tile2 = new Tile(texTile);
	Tile *tile3 = new Tile(texTile);
	Tile *testTile = new Tile(texHighlightTile);

	GUIComponent *topBar = new GUIComponent(texGUIBack, GUIComponent::Type::_box);
	GUIComponent *button1 = new GUIComponent(texGUIBackDark, GUIComponent::Type::_toggle);
	GUIComponent *button2 = new GUIComponent(texGUIBackDark, GUIComponent::Type::_toggle);

	topBar -> SetScale(window.getSize().x / topBar->GetWidth(), 32 / button2 -> GetHeight()); 
	button1 -> SetScale(32 * 5 / button1->GetWidth(), 32 / button1 -> GetHeight()); 
	button2 -> SetScale(32 * 6 / button2->GetWidth(), 32 / button2 -> GetHeight()); 
	
	topBar -> SetPosition(0, 0);
	button1 -> SetPosition(0, 0);
	button2 -> SetPosition(window.getSize().x - button2->GetWidth(), 0);
	
	_gui->Add("c", topBar);
	_gui->Add("a", button2);
	_gui->Add("b", button1);

	GUIComponent *tileOptions = new GUIComponent(texGUIBack, GUIComponent::Type::_box);

	tileOptions -> SetScale(32 * 6 / tileOptions->GetWidth(), 32 * 23 / tileOptions->GetHeight());
	tileOptions -> SetPosition(window.getSize().x - tileOptions->GetWidth(), topBar->GetY() + topBar->GetHeight());

	_gui->Add("d", tileOptions);
	GUIComponent *optionsListRight = new GUIComponent(texArrowRight, texArrowRightHover, GUIComponent::Type::_button);
	GUIComponent *optionsListLeft = new GUIComponent(texArrowLeft, texArrowLeftHover, GUIComponent::Type::_button);
	GUIComponent *grassOption = new GUIComponent(texButton, texButtonHover, GUIComponent::Type::_toggle);
	GUIComponent *waterOption = new GUIComponent(texButton, texButtonHover, GUIComponent::Type::_toggle);
	GUIComponent *dirtOption = new GUIComponent(texButton, texButtonHover, GUIComponent::Type::_toggle);
	GUIComponent *sandOption = new GUIComponent(texButton, texButtonHover, GUIComponent::Type::_toggle);
	GUIComponent *deepWaterOption = new GUIComponent(texButton, texButtonHover, GUIComponent::Type::_toggle);
	GUIComponent *grassOptionIcon = new GUIComponent(texGrassTile, texButtonHover, GUIComponent::Type::_box);
	GUIComponent *grassCheckBox = new GUIComponent(texSmallBox, texSmallBox, texSmallBoxClicked, GUIComponent::Type::_toggle);

	int offsetScalar = 1;
	sf::Vector2f tileTypeButtonScale = sf::Vector2f(32 * 4 / grassOption->GetWidth(), 32 * 1 / grassOption->GetHeight());
	sf::Vector2f tileTypeButtonPos = sf::Vector2f(tileOptions->GetX() + 32, tileOptions->GetY());

	optionsListRight -> SetScale(32 / optionsListRight->GetWidth(), tileTypeButtonScale.y);
	optionsListRight -> SetPosition(button2->GetX() + button2->GetWidth() - optionsListRight->GetWidth(), button2->GetY());

	optionsListLeft -> SetScale(32 / optionsListLeft->GetWidth(), tileTypeButtonScale.y);
	optionsListLeft -> SetPosition(button2->GetX(), button2->GetY());

	tileTypeButtonPos.y += 32;
	grassOption -> SetScale(tileTypeButtonScale.x, tileTypeButtonScale.y);
	grassOption -> SetPosition(tileTypeButtonPos.x, tileTypeButtonPos.y);
	grassCheckBox -> SetScale(32 * 1 / grassCheckBox->GetWidth(), 32 * 1 / grassCheckBox->GetHeight());
	grassCheckBox -> SetPosition(tileTypeButtonPos.x + 32 * 3, tileTypeButtonPos.y);	
	grassOptionIcon -> SetPosition(tileOptions->GetX() + 32 * 5, tileOptions->GetY() + 32);	
	offsetScalar++;
	tileTypeButtonPos.y += 64;
	waterOption -> SetScale(tileTypeButtonScale.x, tileTypeButtonScale.y);
	waterOption ->  SetPosition(tileTypeButtonPos.x, tileTypeButtonPos.y);
	offsetScalar++;
	tileTypeButtonPos.y += 64;
	dirtOption -> SetScale(tileTypeButtonScale.x, tileTypeButtonScale.y);
	dirtOption ->  SetPosition(tileTypeButtonPos.x, tileTypeButtonPos.y);
	offsetScalar++;
	tileTypeButtonPos.y += 64;
	sandOption -> SetScale(tileTypeButtonScale.x, tileTypeButtonScale.y);
	sandOption ->  SetPosition(tileTypeButtonPos.x, tileTypeButtonPos.y);
	offsetScalar++;
	tileTypeButtonPos.y += 64;
	deepWaterOption -> SetScale(tileTypeButtonScale.x, tileTypeButtonScale.y);
	deepWaterOption ->  SetPosition(tileTypeButtonPos.x, tileTypeButtonPos.y);

	_gui->Add("e", grassOption);
	_gui->Add("f", waterOption);
	_gui->Add("g", dirtOption);
	_gui->Add("h", sandOption);
	_gui->Add("i", deepWaterOption);
	_gui->Add("j", optionsListRight);
	_gui->Add("k", optionsListLeft);
	_gui->Add("check", grassCheckBox);
	//_gui->Add("g", grassOptionIcon);
	
	

	tile1 -> SetPosition(map.getGlobalBounds().left, map.getGlobalBounds().top);
	tile2 -> SetPosition(map.getGlobalBounds().left + 32, map.getGlobalBounds().top);
	tile3 -> SetPosition(map.getGlobalBounds().left + 64, map.getGlobalBounds().top);

	const int _mapWidth = (int)map.getLocalBounds().width / 32;
	const int _mapHeight = (int)map.getLocalBounds().height / 32;

	std::vector<std::vector<Tile>> tileMap;
	tileMap.resize(_mapWidth);
	for(unsigned int i = 0; i < tileMap.size(); ++i) {
		tileMap[i].resize(_mapHeight);
	}

	for(unsigned int i = 0; i < tileMap.size(); ++i) {
		for (unsigned int j = 0; j < tileMap[i].size(); ++j) {
			Tile *tmp = new Tile(texTile);
			tileMap[i][j] = *tmp;
			tileMap[i][j].SetPosition(map.getGlobalBounds().left + i * 32, map.getGlobalBounds().top + j * 32);

			//printf("Floats: %4.f %4.f", tileMap[i][j].GetX(), tileMap[i][j].GetY());
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

	sf::Text position;
	position.setString("<0, 0> - <0, 0>"); // The startText will contain the position of the cursor
	position.setPosition(10.f, 10.f);
	position.setColor(sf::Color::White);

	sf::Vector2i pos = sf::Mouse::getPosition(); // We will keep track of the old mouse position

	bool moved = true; // Did the views move?
	std::stringstream ss; // Used to convert integers and floats to strings

	while(window.isOpen()) // As long as the window is open
	{
		sf::Event event; // Normal event handling

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed) {
				window.close();
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
				testTile->SetPosition(tileMap[i][j].GetX(), tileMap[i][j].GetY());
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
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
				}
			}

			if(_gui->Contains((sf::Vector2<float>)(pos))) {
				window.setMouseCursorVisible(true);
			} else {
				window.setMouseCursorVisible(false);
			}
		}

		window.clear(); // Remove old content

		window.setView(standard);
		window.draw(tile1 -> GetSprite());
		window.draw(tile2 -> GetSprite());
		window.draw(tile3 -> GetSprite());


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

		if (button1->IsClicked() && button2->GetY() + button2->GetHeight() > 0) {
			button2->SetPosition(button2->GetX(), button2->GetY() - 5);
		} else if (button2->GetY() < 0) {
			button2->SetPosition(button2->GetX(), button2->GetY() + 5);
		} else {
			button2->SetPosition(button2->GetX(), 0);
		}
		_gui->DrawAll(window);

		
		sf::Text startText("Y: " + std::to_string((int)(button1->GetY())), _font);
		startText.setCharacterSize(button1->GetHeight() / 2);
			startText.setStyle(sf::Text::Bold);
			startText.setColor(sf::Color::Red);
			startText.setPosition(button1->GetX() + button1->GetWidth() / 2 - startText.getLocalBounds().width / 2, 
				button1->GetY() + button1->GetHeight() / 2 - startText.getCharacterSize() / 2);
			// Draw it
			window.draw(startText);

		sf::Text tileOptionsLabel("Tile Type", _font);
		tileOptionsLabel.setCharacterSize(button1->GetHeight() / 1.5);
			//tileOptionsLabel.setStyle(sf::Text::Bold);
			tileOptionsLabel.setColor(sf::Color::White);
			tileOptionsLabel.setPosition(button2->GetX() + button2->GetWidth() / 2 - tileOptionsLabel.getLocalBounds().width / 2, 
				button1->GetY() + button1->GetHeight() / 2 - tileOptionsLabel.getCharacterSize() / 2 - 3);
			// Draw it
			window.draw(tileOptionsLabel);

		sf::Text grassLabel("Grass", _font);
		grassLabel.setCharacterSize(grassOption->GetHeight() / 1.5);
			//tileOptionsLabel.setStyle(sf::Text::Bold);
			grassLabel.setColor(sf::Color::White);
			grassLabel.setPosition(grassOption->GetX() + 15, 
				grassOption->GetY() + grassOption->GetHeight() / 2 - grassLabel.getCharacterSize() / 2 - 3);
			// Draw it
			window.draw(grassLabel);
		window.draw(link);


		window.display(); // Show everything
	}
	}
	return 0;
}

