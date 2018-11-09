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

	// Create test objects
	Player ourPlayer;
	ourPlayer.SetPosition(0.0f, 0.0f);
	Coin ourCoin;
	ourCoin.SetPosition(300.0f, 300.0f);
	Score ourScore;
	ourScore.SetPlayer(&ourPlayer);
	Key ourKey;
	ourKey.SetPosition(750.0f, 500.0f);
	Exit ourExit;
	ourExit.SetPosition(1000.0f, 150.0f);
	ourExit.SetPlayer(&ourPlayer);
	Wall ourWall;
	ourWall.SetPosition(700.0f, 800.0f);


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

		// TODO: Update all game objects
		if (ourPlayer.isActive())
		{
			ourPlayer.Update(frameTime);
		}
		if (ourCoin.isActive())
		{
			ourCoin.Update(frameTime);
		}
		if (ourScore.isActive())
		{
			ourScore.Update(frameTime);
		}
		if (ourKey.isActive())
		{
			ourKey.Update(frameTime);
		}
		if (ourExit.isActive())
		{
			ourExit.Update(frameTime);
		}
		if (ourWall.isActive())
		{
			ourWall.Update(frameTime);
		}

		// -----------------------------------------------
		// Collision Section
		// -----------------------------------------------

		// TODO: Collision detection
		if (ourCoin.isActive() && ourPlayer.isActive())
		{
			if (ourCoin.GetBounds().intersects(ourPlayer.GetBounds()))
			{
				ourCoin.Collide(ourPlayer);
			}
		}

		if (ourKey.isActive() && ourPlayer.isActive())
		{
			if (ourKey.GetBounds().intersects(ourPlayer.GetBounds()))
			{
				ourKey.Collide(ourPlayer);
			}
		}
		if (ourWall.isActive() && ourPlayer.isActive())
		{
			if (ourWall.GetBounds().intersects(ourPlayer.GetBounds()))
			{
				ourPlayer.Collide(ourWall);
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
		// TODO: Draw game objects
		if (ourExit.isActive())
			ourExit.Draw(gameWindow);
		if (ourPlayer.isActive())
			ourPlayer.Draw(gameWindow);
		if (ourCoin.isActive())
			ourCoin.Draw(gameWindow);
		if (ourKey.isActive())
			ourKey.Draw(gameWindow);
		if (ourWall.isActive())
			ourWall.Draw(gameWindow);
		


		// Draw UI to the window
		gameWindow.setView(gameWindow.getDefaultView());
		// TODO: Draw UI objects
		if (ourScore.isActive())
			ourScore.Draw(gameWindow);

		// Display the window contents on the screen
		gameWindow.display();

		///---------------------------------------------
		///END DRAW
		///---------------------------------------------

	} // End of Game Loop

	return 0;

} // End of main() Function