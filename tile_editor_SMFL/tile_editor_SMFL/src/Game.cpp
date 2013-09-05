#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "GameBall.h"

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;
	
	_mainWindow.create(sf::VideoMode(1024,768,32),"Pang!");
	_mainCamera.reset(sf::FloatRect(0, 0, 400, 200));
	_mainWindow.setView(_mainCamera);

	PlayerPaddle *player1 = new PlayerPaddle();
	player1->SetPosition((SCREEN_WIDTH/2),700);
	_gameObjectManager.Add("Paddle1",player1);

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2)-15);
	_gameObjectManager.Add("Ball",ball);
	_gameState= Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}

const sf::Event& Game::GetInput() 
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

void Game::GameLoop()
{
	switch(_gameState)
	{
		case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Game::ShowingSplash:
			{
				
				ShowSplashScreen();
				break;
			}
		case Game::Playing:
			{
				sf::Event currentEvent;
				_mainWindow.pollEvent(currentEvent);
				_mainWindow.clear(sf::Color(255,0,0));
				// move the view at point (200, 200)
				_mainCamera.setCenter(200, 200);

				// move the view by an offset of (100, 100) (so its final position is (300, 300))
				_mainCamera.move(100, 100);

				_gameObjectManager.UpdateAll();
				_gameObjectManager.DrawAll(_mainWindow);
				_mainWindow.display();
				
				if(currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

				if(currentEvent.type == sf::Event::KeyPressed)
					{
						if(currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
						if(currentEvent.key.code == sf::Keyboard::Up) Game::_cameraY += 5;
						if(currentEvent.key.code == sf::Keyboard::Down) Game:: _cameraY -= 5;
						if(currentEvent.key.code == sf::Keyboard::Right) Game:: _cameraX += 5;
						if(currentEvent.key.code == sf::Keyboard::Left) Game:: _cameraX -= 5;

					}
				}
				break;
			
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::View Game::_mainCamera;
float Game::_cameraX = 100;
float Game::_cameraY = 100;