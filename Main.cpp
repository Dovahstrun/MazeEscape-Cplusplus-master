// Library Includes
#include <SFML/Window.hpp>	
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

// Project Includes
#include "AssetManager.h"
#include "Wall.h"
#include "Exit.h"
#include "Player.h"
#include "Baddy.h"
#include "score.h"
#include "Coin.h"
#include "Key.h"

// The main() Function - entry point for our program
int main()
{
	///-------------------------------------------------
	///SETUP
	///-------------------------------------------------

	// Window - to draw to the screen
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Maze Escape", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);

	// Seed our random number generator 
	srand(time(NULL));

	// Create AssetManager
	AssetManager assets;

	// Game Clock - to keep track of time passed each frame
	sf::Clock gameClock;

	// Game state
	bool playing = false;

	// Game camera
	sf::View camera = gameWindow.getDefaultView();

	//Game object lists
	std::vector<GameObject*> updateList;
	std::vector<GameObject*> drawSpriteList;
	std::vector<GameObject*> drawUIList;

	std::vector<std::pair<GameObject*, GameObject*> > collisionList;

	// Create test objects

	Player ourPlayer;
	ourPlayer.SetPosition(0.0f, 0.0f);
	updateList.push_back(&ourPlayer);
	

	Coin ourCoin;
	ourCoin.SetPosition(300.0f, 300.0f);
	updateList.push_back(&ourCoin);
	collisionList.push_back(std::make_pair(&ourCoin, &ourPlayer));
	

	Score ourScore;
	ourScore.SetPlayer(&ourPlayer);
	updateList.push_back(&ourScore);
	drawUIList.push_back(&ourScore);

	Key ourKey;
	ourKey.SetPosition(750.0f, 500.0f);
	updateList.push_back(&ourKey);
	collisionList.push_back(std::make_pair(&ourKey, &ourPlayer));
	

	Exit ourExit;
	ourExit.SetPosition(1000.0f, 150.0f);
	ourExit.SetPlayer(&ourPlayer);
	updateList.push_back(&ourExit);
	

	Wall ourWall;
	ourWall.SetPosition(700.0f, 800.0f);
	updateList.push_back(&ourWall);
	collisionList.push_back(std::make_pair(&ourPlayer, &ourWall));
	

	//Add objects to draw lists
	drawSpriteList.push_back(&ourCoin);
	drawSpriteList.push_back(&ourKey);
	drawSpriteList.push_back(&ourExit);
	drawSpriteList.push_back(&ourWall);
	drawSpriteList.push_back(&ourPlayer);

	///-------------------------------------------------
	///END SETUP
	///-------------------------------------------------



	///-------------------------------------------------
	///GAME LOOP
	///-------------------------------------------------
	while (gameWindow.isOpen())
	{
		///---------------------------------------------
		///INPUT
		///---------------------------------------------

		// Check all events since the last frame and process 
		// each one until there are no more
		sf::Event gameEvent;
		while (gameWindow.pollEvent(gameEvent))
		{
			// TODO: Pass event to input objects


			// Did the player try to close the window?
			if (gameEvent.type == sf::Event::Closed)
			{
				// If so, call the close function on the window.
				gameWindow.close();
			}

		} // End event polling loop

		///---------------------------------------------
		///END INPUT
		///---------------------------------------------



		///---------------------------------------------
		///UPDATE
		///---------------------------------------------

		// Get the time passed since the last frame and restart our game clock
		sf::Time frameTime = gameClock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return 0;
		}

		//Update all game objects
		for (int i = 0; i < updateList.size(); ++i)
		{
			if (updateList[i]->isActive())
			{
				updateList[i]->Update(frameTime);
			}
		}

		// -----------------------------------------------
		// Collision Section
		// -----------------------------------------------

		for (int i = 0; i < collisionList.size(); ++i)
		{
			GameObject* handler = collisionList[i].first;
			GameObject* collider = collisionList[i].second;


			if (handler->isActive() && collider->isActive())
				{
					if (handler->GetBounds().intersects(collider->GetBounds()))
					{
						handler->Collide(*collider);
					}
				}
		}

		///---------------------------------------------
		///END UPDATE
		///---------------------------------------------



		///---------------------------------------------
		///DRAW
		///---------------------------------------------
		// Clear the window to a single colour
		gameWindow.clear(sf::Color::Black);

		// Draw game world to the window
		gameWindow.setView(camera);
		//Draw game objects
		for (int i = 0; i < drawSpriteList.size(); ++i)
		{
			if (drawSpriteList[i]->isActive())
			{
				drawSpriteList[i]->Draw(gameWindow);
			}
		}
		


		// Draw UI to the window
		gameWindow.setView(gameWindow.getDefaultView());
		//Draw UI objects
		for (int i = 0; i < drawUIList.size(); ++i)
		{
			if (drawUIList[i]->isActive())
			{
				drawUIList[i]->Draw(gameWindow);
			}
		}

		// Display the window contents on the screen
		gameWindow.display();

		///---------------------------------------------
		///END DRAW
		///---------------------------------------------

	} // End of Game Loop

	return 0;

} // End of main() Function