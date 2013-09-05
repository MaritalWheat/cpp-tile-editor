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
	sf::RenderWindow window(sf::VideoMode(1024, 756), "Using sf::View", sf::Style::Close | sf::Style::Titlebar); // Create window
	window.setFramerateLimit(60); // Set a framrate limit to reduce the CPU load
	window.setMouseCursorVisible(false); // Hide the cursor

	sf::Texture texOverlay; // Create the overlay texture and sprite
	texOverlay.loadFromFile("Assets/overlay.png");
	sf::Sprite overlay(texOverlay);
	overlay.setPosition(100.f, 100.f);

	sf::Texture texButton;
	texButton.loadFromFile("Assets/Paddle.png");

	

	sf::Texture texMap; // Create the world texture and sprite
	texMap.setSmooth(true);
	texMap.loadFromFile("Assets/world.png");
	sf::Sprite map(texMap);
	
	sf::Texture texTile;
	texTile.loadFromFile("Assets/EmptyTile.png");

	sf::Texture texPlacerTile;
	texPlacerTile.loadFromFile("Assets/Grass.png");

	GUIManager *_gui = new GUIManager();
	Tile *tile1 = new Tile(texTile);
	Tile *tile2 = new Tile(texTile);
	Tile *tile3 = new Tile(texTile);
	Tile *testTile = new Tile(texPlacerTile);

	GUIComponent *button1 = new GUIComponent(texButton);
	GUIComponent *button2 = new GUIComponent(texButton);

	button1 -> SetScale(2, 2);
	button2 -> SetScale(2, 2);
	
	button1 -> SetPosition(0, 0);
	button2 -> SetPosition(window.getSize().x - button2->GetWidth(), 0);
	
	_gui->Add("1", button1);
	_gui->Add("2", button2);

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

			printf("Floats: %4.f %4.f", tileMap[i][j].GetX(), tileMap[i][j].GetY());
		}
	}

	std::vector<Tile> _placedTiles;
	int _size = 0;
	_placedTiles.resize(0);


	sf::Texture texLink; // Create the link texture and sprite which will be out cursor
	texLink.loadFromFile("Assets/link.png");
	sf::Sprite link(texLink);
	link.setOrigin(8.f, 8.f); // The cursors point should be in the middle
	float _cameraPos = 0.f;
	
	
	sf::View fixed = window.getView(); // The 'fixed' view will never change

	sf::View standard = fixed; // The 'standard' view will be the one that gets always displayed
	link.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));

	unsigned int size = 200; // The 'minimap' view will show a smaller picture of the map
	sf::View minimap(sf::FloatRect(standard.getCenter().x, standard.getCenter().y, static_cast<float>(size), static_cast<float>(window.getSize().y*size/window.getSize().x)));
	minimap.setViewport(sf::FloatRect(1.f-static_cast<float>(minimap.getSize().x)/window.getSize().x-0.02f, 1.f-static_cast<float>(minimap.getSize().y)/window.getSize().y-0.02f, static_cast<float>(minimap.getSize().x)/window.getSize().x, static_cast<float>(minimap.getSize().y)/window.getSize().y));
	minimap.zoom(4.f);

	// The 'left' and the 'right' view will be used for splitscreen displays
	sf::View left(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x/2), static_cast<float>(window.getSize().y)));
	left.setViewport(sf::FloatRect(0.f, 0.f, 0.5, 1.f));
	sf::View right(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x/2), static_cast<float>(window.getSize().y)));
	right.setViewport(sf::FloatRect(0.5, 0.f, 0.5, 1.f));
	right.move(100.f, 100.f); // The 'right' view should be set a bit diffrent to notice the difference

	sf::RectangleShape miniback; // We want to draw a rectangle behind the minimap
	miniback.setPosition(minimap.getViewport().left*window.getSize().x-5, minimap.getViewport().top*window.getSize().y-5);
	miniback.setSize(sf::Vector2f(minimap.getViewport().width*window.getSize().x+10, minimap.getViewport().height*window.getSize().y+10));
	miniback.setFillColor(sf::Color(160, 8, 8));

	sf::Text position;
	position.setString("<0, 0> - <0, 0>"); // The text will contain the position of the cursor
	position.setPosition(10.f, 10.f);
	position.setColor(sf::Color::White);

	sf::Vector2i pos = sf::Mouse::getPosition(); // We will keep track of the old mouse position

	bool overlayClosed = false; // Is the overlay closed?
	bool toggleSplit = false; // Should the screen be split?
	bool moved = true; // Did the views move?
	std::stringstream ss; // Used to convert integers and floats to strings

	while(window.isOpen()) // As long as the window is open
	{
		sf::Event event; // Normal event handling

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			else if(overlayClosed && event.type == sf::Event::MouseWheelMoved) // Zomm in or out if the mouse wheel moves
			{
				standard.zoom(1.f+event.mouseWheel.delta*0.1f);
				left.zoom(1.f+event.mouseWheel.delta*0.1f);
				right.zoom(1.f+event.mouseWheel.delta*0.1f);
				moved = true;
			}
			else if(overlayClosed && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q)
			{
				toggleSplit = !toggleSplit; // Split or unsplit the screen only on releasing the key Q
			}
		}

		if(overlayClosed)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // Rotate counter clockwise
			{
				standard.rotate(0.25f);
				minimap.rotate(0.25f);
				left.rotate(0.25f);
				right.rotate(0.25f);
				moved = true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)) // Rotate clockwise
			{
				standard.rotate(-0.25f);
				minimap.rotate(-0.25f);
				left.rotate(-0.25f);
				right.rotate(-0.25f);
				moved = true;
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				// Move left
				//link.setPosition(link.getPosition().x - 3, link.getPosition().y);
				//standard.reset(link.getPosition().x, link.getPosition().y, standard.getSize().x, standard.getSize().y);
				if(_cameraPos > map.getPosition().x + 3) {
					standard.move(-3.f, 0.f);
					_cameraPos -= 3;
				} else {
					link.setPosition(link.getPosition().x - 3, link.getPosition().y);
					_cameraPos -= 3;
				}
				//minimap.move(-4.f, 0.f);
				//left.move(-4.f, 0.f);
				//right.move(-4.f, 0.f);
				moved = true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				// Move right
				//link.setPosition(link.getPosition().x + 3, link.getPosition().y);
				//standard.set
				if (_cameraPos > map.getPosition().x) {
					standard.move(3.f, 0.f);
				} else { 
					link.setPosition(link.getPosition().x + 3, link.getPosition().y);
				}
				_cameraPos += 3;
				//minimap.move(4.f, 0.f);
				//left.move(4.f, 0.f);
				//right.move(4.f, 0.f);
				moved = true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				// Move up
				if(link.getPosition().y  - link.getLocalBounds().height / 2 - 3 > tile1 -> GetY() + tile1 -> GetHeight()) {
					link.setPosition(link.getPosition().x, link.getPosition().y - 3);
				}
				//standard.move(0.f, -4.f);
				//minimap.move(0.f, -4.f);
				//left.move(0.f, -4.f);
				//right.move(0.f, -4.f);
				moved = true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				// Move down
				link.setPosition(link.getPosition().x, link.getPosition().y + 3);
				//standard.move(0.f, 4.f);
				//minimap.move(0.f, 4.f);
				//left.move(0.f, 4.f);
				//right.move(0.f, 4.f);
				moved = true;
			}
		}
		else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			overlayClosed = true; // Close overlay

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
					Tile *tmp = new Tile(texPlacerTile);
					_placedTiles[_size - 1] = *tmp;
					_placedTiles[_size - 1].SetPosition(tileMap[i][j].GetX(), tileMap[i][j].GetY());
				}
			}

			_gui->Contains((sf::Vector2<float>)(pos));


			
				


			/*link.setPosition(static_cast<sf::Vector2f>(pos)); // Set Link to the new position
			
			// Convert the position:
			//		left: relative position on the window
			//		right: relative position to the standard view
			ss.str("");
			ss << "<" << pos.x << ", " << pos.y << ">\t<" << window.mapPixelToCoords(pos, standard).x << ", " << window.mapPixelToCoords(pos, standard).y << ">";
			position.setString(ss.str());*/
		}

		window.clear(); // Remove old content

		if(!toggleSplit) // Draw one map for none split screen
		{
			//standard.setSize(standard.getSize().x, standard.getSize().y * 2);
			//standard.setCenter(standard.getSize() *.5f);
			window.setView(standard);
			//window.draw(map);		
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
		}
		else // Draw two maps for split screen
		{
			window.setView(left);
			window.draw(map);
			window.setView(right);
			window.draw(map);
		}

		window.setView(fixed); // Draw 'GUI' elements with fixed positions
		window.draw(position);
		window.draw(miniback);

		window.setView(minimap); // Draw minimap
		window.draw(map);


		window.setView(fixed);
		if(!overlayClosed)
			window.draw(overlay);
		_gui->DrawAll(window);
		//button1 -> SetColor(sf::Color::Green);
		window.draw(button1->GetSprite());
		window.draw(button2->GetSprite());
		window.draw(link);


		window.display(); // Show everything
	}

	return 0;
}
