//Library Includes
#include <iostream>
#include <fstream>

//Project Includes

#include "Level.h"
#include "Wall.h"
#include "Exit.h"
#include "Player.h"
#include "Baddy.h"
#include "score.h"
#include "Coin.h"
#include "Key.h"
#include "Hazard.h"

Level::Level()
	: m_player(nullptr)
	, m_updateList()
	, m_drawSpriteList()
	, m_drawUIList()
	, m_collisionList()
	, m_currentLevel(0)
{
	loadLevel(1);
}

void Level::Draw(sf::RenderTarget & _target)
{
	//Create and update camera
	sf::View camera = _target.getDefaultView();
	camera.setCenter(m_player->GetPosition());
	//TODO: Follow player with camera

	// Draw game world to the window
	_target.setView(camera);
	//Draw game objects
	for (int i = 0; i < m_drawSpriteList.size(); ++i)
	{
		if (m_drawSpriteList[i]->isActive())
		{
			m_drawSpriteList[i]->Draw(_target);
		}
	}



	// Draw UI to the window
	_target.setView(_target.getDefaultView());
	//Draw UI objects
	for (int i = 0; i < m_drawUIList.size(); ++i)
	{
		if (m_drawUIList[i]->isActive())
		{
			m_drawUIList[i]->Draw(_target);
		}
	}
}

void Level::Update(sf::Time _frameTime)
{
	//Update
	for (int i = 0; i < m_updateList.size(); ++i)
	{
		if (m_updateList[i]->isActive())
		{
			m_updateList[i]->Update(_frameTime);
		}
	}


	// -----------------------------------------------
	// Collision Section
	// -----------------------------------------------

	for (int i = 0; i < m_collisionList.size(); ++i)
	{
		GameObject* handler = m_collisionList[i].first;
		GameObject* collider = m_collisionList[i].second;


		if (handler->isActive() && collider->isActive())
		{
			if (handler->GetBounds().intersects(collider->GetBounds()))
			{
				handler->Collide(*collider);
			}
		}
	}
}

void Level::loadLevel(int _levelToLoad)
{

	///Cleanup the old level

	//Delete any data already in the level
	for (int i = 0; i < m_updateList.size(); ++i)
	{
		delete m_updateList[i];
	}

	//FUCKING THING NOT WORKING, DELETE IS BREAKING IT, REMEMBER THIS FUCKING THING FOR GODS SAKE OH MY GOD

	//Clear out the lists
	m_updateList.clear();
	m_drawSpriteList.clear();
	m_drawUIList.clear();
	m_collisionList.clear();

	///Setup everything

	//Set current level
	m_currentLevel = _levelToLoad;

	//Set up all the game objects

	//Open our file for reading
	std::ifstream inFile;
	std::string fileName = "levels/Level" + std::to_string(m_currentLevel) + ".txt";
	inFile.open(fileName);

	//Make sure the file was opened
	if (!inFile)
	{
		std::cerr << "Unable to open file " + fileName;
		exit(1); //Call system to stop program with error	
	}

	//Set the starting x and y coords used to position level objects
	float x = 0.0f;
	float y = 0.0f;

	//Define the spacing we will use for our grid
	const float Y_SPACE = 100.0f;
	const float X_SPACE = 100.0f;

	//Create the player first as other objects will need to reference it
	Player* ourPlayer = new Player();
	m_player = ourPlayer;

	//Reading each character one by one from the file...
	char ch;
	//Each time, try to read the next character, execute body of loop
	while (inFile >> std::noskipws >> ch)//the noskipws means we will include the white space (spaces)
	{
		//Perform actions based on what character was read in
		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == 'W')
		{
			Wall* ourWall = new Wall();
			ourWall->SetPosition(x, y);
			m_updateList.push_back(ourWall);
			m_collisionList.push_back(std::make_pair(ourPlayer, ourWall));
			m_drawSpriteList.push_back(ourWall);
		}
		else if (ch == 'C')
		{
			Coin* ourCoin = new Coin();
			ourCoin->SetPosition(x, y);
			m_updateList.push_back(ourCoin);
			m_collisionList.push_back(std::make_pair(ourCoin, ourPlayer));
			m_drawSpriteList.push_back(ourCoin);
		}
		else if (ch == 'K')
		{
			Key* ourKey = new Key();
			ourKey->SetPosition(x, y);
			m_updateList.push_back(ourKey);
			m_collisionList.push_back(std::make_pair(ourKey, ourPlayer));
			m_drawSpriteList.push_back(ourKey);
		}
		else if (ch == 'E')
		{
			Exit* ourExit = new Exit();
			ourExit->SetPosition(x, y);
			ourExit->SetPlayer(ourPlayer);
			m_updateList.push_back(ourExit);
			m_collisionList.push_back(std::make_pair(ourExit, ourPlayer));
			m_drawSpriteList.push_back(ourExit);
		}
		else if (ch == 'H')
		{
			Hazard* ourHazard = new Hazard();
			ourHazard->SetPosition(x, y);
			m_updateList.push_back(ourHazard);
			m_collisionList.push_back(std::make_pair(ourHazard, ourPlayer));
			m_drawSpriteList.push_back(ourHazard);
		}
		else if (ch == 'P')
		{
			ourPlayer->SetPosition(x, y);
			ourPlayer->setLevel(this);
			m_updateList.push_back(ourPlayer);
			m_drawSpriteList.push_back(ourPlayer);
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}
	}

	//Close the file now that we're done
	inFile.close();

	//Score - position not dependent on level
	Score* ourScore = new Score();
	ourScore->SetPlayer(ourPlayer);
	m_updateList.push_back(ourScore);
	m_drawUIList.push_back(ourScore);
	
}

void Level::ReloadLevel()
{
	loadLevel(m_currentLevel);
}

int Level::GetCurrentLevel()
{
	return m_currentLevel;
}
